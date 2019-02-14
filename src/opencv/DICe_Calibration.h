// @HEADER
// ************************************************************************
//
//               Digital Image Correlation Engine (DICe)
//                 Copyright 2015 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NTESS OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact: Dan Turner (dzturne@sandia.gov)
//
// ************************************************************************
// @HEADER

#ifndef DICE_CALIBRATION_H
#define DICE_CALIBRATION_H

#include <DICe.h>

#include "opencv2/core/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <Teuchos_ParameterList.hpp>
#include <cassert>

namespace DICe {

// forward dec for camera system return type of calibration
class Camera_System;

/// \class DICe::Calibration
/// \brief A class for processing calibration target images and determining camera calibration parameters
///
/// This class uses the OpenCV calibration routine and is currently limited to one or two cameras.
/// The extraction routine supports dot targets with 3 "donut" marker dots to specify the axes or
/// checkerboard calibration targets.
class DICE_LIB_DLL_EXPORT
Calibration {
public:

  /// types of calibration targets that may be used
  enum Target_Type {
    CHECKER_BOARD = 0,
    BLACK_ON_WHITE_W_DONUT_DOTS,
    WHITE_ON_BLACK_W_DONUT_DOTS,
    //DON"T ADD ANY BELOW MAX
    MAX_TARGET_TYPE,
    NO_SUCH_TARGET_TYPE
  };

  static std::string to_string(Target_Type in){
    assert(in < MAX_TARGET_TYPE);
    const static char * targetStrings[] = {
      "CHECKER_BOARD",
      "BLACK_ON_WHITE_W_DONUT_DOTS",
      "WHITE_ON_BLACK_W_DONUT_DOTS"
    };
    return targetStrings[in];
  };

  static Target_Type string_to_target_type(std::string & in){
    // convert the string to uppercase
    std::transform(in.begin(), in.end(),in.begin(),::toupper);
    for(int_t i=0;i<MAX_TARGET_TYPE;++i){
      if(to_string(static_cast<Target_Type>(i))==in) return static_cast<Target_Type>(i);
    }
    std::cout << "Error: Target_Type " << in << " does not exist." << std::endl;
    TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument,"");
    return NO_SUCH_TARGET_TYPE; // prevent no return errors
  }

  /// \brief constructor with no arguments. It sets the default calibration options and no output to the console
  Calibration(const std::string & cal_input_file);

  /// \brief constructor with no arguments. It sets the default calibration options and no output to the console
  Calibration(const Teuchos::RCP<Teuchos::ParameterList> parameter_list){
    init(parameter_list);
  }

  /// initialize the calibration
  void init(const Teuchos::RCP<Teuchos::ParameterList> parameter_list);

  /// destructor
  virtual ~Calibration(){};

  /// returns the number of images used (for each camera)
  size_t num_images() const { return image_list_[0].size(); };

  /// returns true if this is a stereo calibration
  bool is_stereo() const { return image_list_.size()==2; };

  /// return the number of cameras
  size_t num_cams() const { return image_list_.size(); };

  /// \brief extract the points from the calibration image
  /// \param threshold_start Optional starting threshold when looking for the marker dots (only used for dot targets)
  /// \param threshold_end Optional ending threshold when looking for the marker dots (only used for dot targets)
  /// \param threshold_step Optional threshold step when looking for the marker dots (only used for dot targets)
  void extract_target_points(const int_t threshold_start = 20,
    const int_t threshold_end = 250,
    const int_t threshold_step = 5);

  /// \brief writes a file with the image list, parameters and all the intersection points from the calibration images
  /// \param filename the name of the file to write (should end in xml)
  void write_calibration_file(const std::string & filename);

  /// \brief perform the calibration and return a camera system object
  Teuchos::RCP<DICe::Camera_System> calibrate(scalar_t & rms_error){
    return calibrate("",rms_error);
  }

  /// returns the rms error of the calibration and writes an output file
  scalar_t calibrate(const std::string & output_file){
    scalar_t rms_error;
    calibrate(output_file,rms_error);
    return rms_error;
  }

  /// overaload the ostream operator for a calibration class
  /// overload the ostream operator to enable std::cout << Calibration << std::endl;, etc.
  friend std::ostream & operator<<(std::ostream & os, const Calibration & cal);

private:

  /// \brief private method that performs the calibration and
  /// can be used as a base method for either outputting a camera system file
  /// or returning a camera system object
  Teuchos::RCP<DICe::Camera_System> calibrate(const std::string & output_file,
    scalar_t & rms_error);

  /// set calibration options
  void set_calibration_options(const Teuchos::ParameterList & opencv_options);

  /// get intersection points from checkerboard target
  void extract_checkerboard_intersections();

  /// trim out the disabled images
  void assemble_intersection_object_points();

  /// \brief extract the points from the calibration image
  /// \param threshold_start Optional starting threshold when looking for the marker dots (only used for dot targets)
  /// \param threshold_end Optional ending threshold when looking for the marker dots (only used for dot targets)
  /// \param threshold_step Optional threshold step when looking for the marker dots (only used for dot targets)
  void extract_dot_target_points(const int_t threshold_start,
    const int_t threshold_end,
    const int_t threshold_step);

  /// uses the openCV blob detector to get possible dot locations
  void get_dot_markers(cv::Mat img,
    std::vector<cv::KeyPoint> & keypoints,
    int_t thresh,
    bool invert);

  /// calculates the image to grid and grid to images coefficients based on the current set of good points
  void calc_trans_coeff(std::vector<cv::KeyPoint> & imgpoints,
    std::vector<cv::KeyPoint> & grdpoints);

  /// filters the possible dots by size, the bounding box and how close they are to the expected grid locations
  void filter_dot_markers(int_t icam,
    int_t i_img, std::vector<cv::KeyPoint> dots,
    std::vector<cv::KeyPoint> & img_points,
    std::vector<cv::KeyPoint> & grd_points,
    float dot_tol,
    cv::Mat out_img,
    bool draw);

  /// reorders the keypoints into origin, x dot, y dot based on the distances between them
  void reorder_keypoints(std::vector<cv::KeyPoint> & keypoints);

  /// creates a quadrilateral that describes the allowable area for valid dots
  void create_bounding_box(std::vector<float> & box_x,
    std::vector<float> & box_y);

  /// transformation from grid location (interger location with (0,0) at the minimum x minimum y location) to image locations
  void grid_to_image(const float & grid_x,
    const float & grid_y,
    float & img_x,
    float & img_y);

  /// transformation from image locations to integer grid locations (0,0) at the minimum x minimum y location
  void image_to_grid(const float & img_x,
    const float & img_y,
    float & grid_x,
    float & grid_y);

  /// checks if a point is in the bounding box quadrilateral
  bool is_in_quadrilateral(const float & x,
    const float & y,
    const std::vector<float> & box_x,
    const std::vector<float> & box_y);

  /// returns the squared distance between two keypoints
  float dist2(cv::KeyPoint pnt1, cv::KeyPoint pnt2);

  /// returns indicies of three distances sorted by decending magnitude
  void order_dist3(std::vector<float> & dist,
    std::vector<int> & dist_order);

  /// the type of calibration target plate
  Target_Type target_type_;
  /// the total number of fiducial markers, intersection, or dots in the x direction on the entire cal target
  int_t num_fiducials_x_;
  /// the total number of fiducial markers, intersection, or dots in the x direction on the entire cal target
  int_t num_fiducials_y_;
  /// the spacing in physical units of the target dots or intersections
  scalar_t target_spacing_;
  /// location of the origin marker point in the x direction measured by the number points from the left most point (pt 0)
  int_t origin_loc_x_;
  /// location of the origin marker point in the y direction measured by the number points from the bottom most point (pt 0)
  int_t origin_loc_y_;
  /// the number of fiducial markers or intersections between the origin and the marker dot on the x axis
  int_t num_fiducials_origin_to_x_marker_;
  /// the number of fiducial markers or intersections between the origin and the marker dot on the y axis
  int_t num_fiducials_origin_to_y_marker_;
  /// true if an intersection image should be drawn
  bool draw_intersection_image_;
  /// if specified, the debug folder is where the debugging images are placed
  std::string debug_folder_;

  /// vector of flags that if true, the image will be included in the calibration image set
  /// used to turn off images that have high error, etc.
  std::vector<bool> include_set_;

  /// size of the cal images
  cv::Size image_size_;

  /// grid points represent the coordinates of the fiducial points
  std::vector<std::vector<cv::Point3f> > grid_points_;
  /// image_points are the x and y image coordinates for the fiducials as located
  std::vector<std::vector<std::vector<std::vector<cv::Point2f> > > > image_points_;

  /// intersection and object point storage used for opencv input arguments
  /// this is the trimmed set of points that excludes images that are deactivated
  std::vector<std::vector<std::vector<cv::Point2f> > > intersection_points_;
  /// the trimmed grid points
  std::vector<std::vector<cv::Point3f> > object_points_;

  /// true if the intersection points have been initialized
  bool has_intersection_points_;

  /// integer representation of the opencv calibration options
  int_t calib_options_;
  /// text for all the calibration options
  std::vector<std::string> calib_options_text_;

  /// images to use for the calibration
  std::vector<std::vector<std::string> > image_list_;

  /// 6 transformation coefficients
  std::vector<scalar_t> img_to_grdx_;
  std::vector<scalar_t> grd_to_imgx_;
  std::vector<scalar_t> img_to_grdy_;
  std::vector<scalar_t> grd_to_imgy_;

  // save a copy of the input params:
  Teuchos::ParameterList input_params_;

};

}// End DICe Namespace

#endif

