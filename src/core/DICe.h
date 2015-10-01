// @HEADER
// ************************************************************************
//
//               Digital Image Correlation Engine (DICe)
//                 Copyright (2014) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
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
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact:
//              Dan Turner   (danielzturner@gmail.com)
//
// ************************************************************************
// @HEADER

#ifndef DICE_H
#define DICE_H

#define DICE_PI 3.14159265358979323846
#define DICE_TWOPI 6.28318530717958647692

#if defined(WIN32)
#  if defined(DICE_LIB_EXPORTS_MODE)
#    define DICE_LIB_DLL_EXPORT __declspec(dllexport)
#  else
#    define DICE_LIB_DLL_EXPORT __declspec(dllimport)
#  endif
#else
#  define DICE_LIB_DLL_EXPORT
#endif

// debugging macros:
#ifdef DICE_DEBUG_MSG
#  define DEBUG_MSG(x) do { std::cout << "[DICe_DEBUG]: " << x << std::endl; } while (0)
#else
#  define DEBUG_MSG(x) do {} while (0)
#endif

// size of the deformation vectors used in the correlation
// includes fields below from 0 to (DICE_DEFORMATION_SIZE-1)
#define DICE_DEFORMATION_SIZE 12

namespace DICe{

/// basic types

#ifdef DICE_USE_DOUBLE
  /// image intensity type
  typedef double intensity_t;
  /// generic scalar type
  typedef double scalar_t;
#else
  /// image intensity type
  typedef float intensity_t;
  /// generic scalar type
  typedef float scalar_t;
#endif

typedef long int int_t;

/// deformation map
struct Def_Map{
  scalar_t u_;
  scalar_t v_;
  scalar_t t_;
  scalar_t ex_;
  scalar_t ey_;
  scalar_t g_;
  Def_Map():
    u_(0.0),
    v_(0.0),
    t_(0.0),
    ex_(0.0),
    ey_(0.0),
    g_(0.0){}
};

/// parameters (all lower case)

/// String parameter names using globals to prevent misspelling in the parameter lists:
const char* const image_grad_use_hierarchical_parallelism = "image_grad_use_hierarchical_parallelism";
/// String parameter name
const char* const image_grad_team_size = "image_grad_team_size";
/// String parameter name
const char* const gauss_filter_images = "gauss_filter_images";
/// String parameter name
const char* const gauss_filter_use_hierarchical_parallelism = "gauss_filter_use_hierarchical_parallelism";
/// String parameter name
const char* const gauss_filter_team_size = "gauss_filter_team_size";
/// String parameter name
const char* const gauss_filter_mask_size = "gauss_filter_mask_size";
/// String parameter name
const char* const correlation_routine = "correlation_routine";
/// String parameter name
const char* const use_global_dic = "use_global_dic";
/// String parameter name
const char* const use_constrained_opt_dic = "use_constrained_opt_dic";
/// String parameter name
const char* const use_integrated_dic = "use_integrated_dic";
/// String parameter name
const char* const use_hvm_stabilization = "use_hvm_stabilization";
/// String parameter name
const char* const interpolation_method = "interpolation_method";
/// String parameter name
const char* const initialization_method = "initialization_method";
/// String parameter name
const char* const optimization_method = "optimization_method";
/// String parameter name
const char* const projection_method = "projection_method";
/// String parameter name
const char* const compute_ref_gradients = "compute_ref_gradients";
/// String parameter name
const char* const compute_def_gradients = "compute_def_gradients";
/// String parameter name
const char* const compute_image_gradients = "compute_image_gradients";
/// String parameter name
const char* const enable_translation = "enable_translation";
/// String parameter name
const char* const enable_rotation = "enable_rotation";
/// String parameter name
const char* const enable_normal_strain = "enable_normal_strain";
/// String parameter name
const char* const enable_shear_strain = "enable_shear_strain";
/// String parameter name
const char* const search_window_size_factor = "search_window_size_factor";
/// String parameter name
const char* const search_window_skip = "search_window_skip";
/// String parameter name
const char* const max_evolution_iterations = "max_evolution_iterations";
/// String parameter name
const char* const max_solver_iterations_fast = "max_solver_iterations_fast";
/// String parameter name
const char* const max_solver_iterations_robust = "max_solver_iterations_robust";
/// String parameter name
const char* const robust_solver_tolerance = "robust_solver_tolerance";
/// String parameter name
const char* const skip_solve_gamma_threshold = "skip_solve_gamma_threshold";
/// String parameter name
const char* const fast_solver_tolerance = "fast_solver_tolerance";
/// String parameter name
const char* const pixel_size_in_mm = "pixel_size_in_mm";
/// String parameter name
const char* const disp_jump_tol = "disp_jump_tol";
/// String parameter name
const char* const theta_jump_tol = "theta_jump_tol";
/// String parameter name
const char* const robust_delta_disp = "robust_delta_disp";
/// String parameter name
const char* const robust_delta_theta = "robust_delta_theta";
/// String parameter name
const char* const output_deformed_subset_images = "output_deformed_subset_images";
/// String parameter name
const char* const output_deformed_subset_intensity_images = "output_deformed_subset_intensity_images";
/// String parameter name
const char* const output_evolved_subset_images = "output_evolved_subset_images";
/// String parameter name
const char* const use_subset_evolution = "use_subset_evolution";
/// String parameter name
const char* const max_iterations = "max_iterations";
/// String parameter name
const char* const tolerance = "tolerance";
/// String parameter name
const char* const output_spec = "output_spec";
/// String parameter name
const char* const output_delimiter = "output_delimiter";
/// String parameter name
const char* const omit_output_row_id = "omit_output_row_id";
/// String parameter name
const char* const obstruction_buffer_size = "obstruction_buffer_size";
/// String parameter name
const char* const obstruction_skin_factor = "obstruction_skin_factor";
/// String parameter name
const char* const use_sl_default_params = "use_sl_default_params";
/// String parameter name
const char* const update_obstructed_pixels_each_iteration = "update_obstructed_pixels_each_iteration";
/// String parameter name
const char* const normalize_gamma_with_active_pixels = "normalize_gamma_with_active_pixels";
/// String parameter name
const char* const use_objective_regularization = "use_objective_regularization";
/// String parameter name
const char* const pixel_integration_order = "pixel_integration_order";

/// enums:
enum Subset_View_Target{
  REF_INTENSITIES=0,
  DEF_INTENSITIES,
  // *** DO NOT PUT NEW ENUMS BELOW THIS ONE ***
  // (this is used for striding and converting enums to strings)
  MAX_SUBSET_VIEW_TARGET,
  NO_SUCH_SUBSET_VIEW_TARGET,
};
/// string names for enums above
static const char * subsetInitModeStrings[] = {
  "FILL_REF_INTENSITIES",
  "FILL_DEF_INTENSITIES"
};

/// Valid names for fields
enum Field_Name {
  // *** DON'T FORGET TO ADD A STRING TO THE fieldNameStrings BELOW IN THE SAME ORDER ***
  //
  // *** ALSO UPDATE THE SIZE OF THE DEFORMATION GIVEN IN #define DICE_DEFORMATION_SIZE
  //     IF MORE DEFORMATION FIELDS ARE ADDED
  // 0
  DISPLACEMENT_X=0,
  // 1
  DISPLACEMENT_Y,
  // 2
  DISPLACEMENT_Z,
  // 3
  ROTATION_X,
  // 4
  ROTATION_Y,
  // 5
  ROTATION_Z,
  // 6
  NORMAL_STRAIN_X,
  // 7
  NORMAL_STRAIN_Y,
  // 8
  NORMAL_STRAIN_Z,
  // 9
  SHEAR_STRAIN_XY,
  // 10
  SHEAR_STRAIN_YZ,
  // 11
  SHEAR_STRAIN_XZ,
  // *** Fields >= DICE_DEFORMATION_SIZE are not part of the deformation state of a subset
  //     but used elsewhere in the schema
  // 12
  COORDINATE_X,
  // 13
  COORDINATE_Y,
  // 14
  COORDINATE_Z,
  // 15
  VAR_X,
  // 16
  VAR_Y,
  // 17
  VAR_Z,
  // 18
  SIGMA,
  // 19
  GAMMA,
  // 20
  MATCH,
  // 21
  ITERATIONS,
  // 22
  STATUS_FLAG,
  // 23
  NEIGHBOR_ID,
  // 24
  CONDITION_NUMBER,
  // *** DO NOT PUT ANY FIELDS UNDER THIS ONE ***
  // (this is how the field stride is automatically set if another field is added)
  MAX_FIELD_NAME,
  NO_SUCH_FIELD_NAME
};

static const char * fieldNameStrings[] = {
  "DISPLACEMENT_X",
  "DISPLACEMENT_Y",
  "DISPLACEMENT_Z",
  "ROTATION_X",
  "ROTATION_Y",
  "ROTATION_Z",
  "NORMAL_STRAIN_X",
  "NORMAL_STRAIN_Y",
  "NORMAL_STRAIN_Z",
  "SHEAR_STRAIN_XY",
  "SHEAR_STRAIN_YZ",
  "SHEAR_STRAIN_XZ",
  "COORDINATE_X",
  "COORDINATE_Y",
  "COORDINATE_Z",
  "VAR_X",
  "VAR_Y",
  "VAR_Z",
  "SIGMA",
  "GAMMA",
  "MATCH",
  "ITERATIONS",
  "STATUS_FLAG",
  "NEIGHBOR_ID",
  "CONDITION_NUMBER"
};

/// Subset_File_Info types
enum Subset_File_Info_Type {
  SUBSET_INFO=0,
  REGION_OF_INTEREST_INFO
};

/// Enum that determines which distributed vector to send
/// the field values to
enum Target_Field_Descriptor {
  ALL_OWNED=0,
  DISTRIBUTED,
  DISTRIBUTED_GROUPED_BY_SEED,
  MAX_TARGET_FIELD_DESCRIPTOR
};

const static char * targetFieldDescriptorStrings[] = {
  "ALL_OWNED",
  "DISTRIBUTED",
  "DISTRIBUTED_GROUPED_BY_SEED"
};

/// Analysis Type
enum Analysis_Type {
  LOCAL_DIC=0,
  GLOBAL_DIC,
  CONSTRAINED_OPT,
  INTEGRATED_DIC,
  // DON'T ADD ANY BELOW THIS
  MAX_ANALYSIS_TYPE,
  NO_SUCH_ANALYSIS_TYPE
};

/// Projection method
enum Projection_Method {
  DISPLACEMENT_BASED=0,
  VELOCITY_BASED,
  MULTISTEP,
  // DON'T ADD ANY BELOW MAX
  MAX_PROJECTION_METHOD,
  NO_SUCH_PROJECTION_METHOD
};

const static char * projectionMethodStrings[] = {
  "DISPLACEMENT_BASED",
  "VELOCITY_BASED",
  "MULTISTEP"
};

/// Initialization method
enum Initialization_Method {
  USE_FIELD_VALUES=0,
  USE_NEIGHBOR_VALUES,
  USE_NEIGHBOR_VALUES_FIRST_STEP_ONLY,
  USE_PHASE_CORRELATION,
  INITIALIZATION_METHOD_NOT_APPLICABLE,
  // DON'T ADD ANY BELOW MAX
  MAX_INITIALIZATION_METHOD,
  NO_SUCH_INITIALIZATION_METHOD
};

const static char * initializationMethodStrings[] = {
  "USE_FIELD_VALUES",
  "USE_NEIGHBOR_VALUES",
  "USE_NEIGHBOR_VALUES_FIRST_STEP_ONLY",
  "USE_PHASE_CORRELATION",
  "INITIALIZATION_METHOD_NOT_APPLICABLE"
};

/// Optimization method
enum Optimization_Method {
  SIMPLEX=0,
  GRADIENT_BASED,
  SIMPLEX_THEN_GRADIENT_BASED,
  GRADIENT_BASED_THEN_SIMPLEX,
  OPTIMIZATION_METHOD_NOT_APPLICABLE,
  // DON'T ADD ANY BELOW MAX
  MAX_OPTIMIZATION_METHOD,
  NO_SUCH_OPTIMIZATION_METHOD
};

const static char * optimizationMethodStrings[] = {
  "SIMPLEX",
  "GRADIENT_BASED",
  "SIMPLEX_THEN_GRADIENT_BASED",
  "GRADIENT_BASED_THEN_SIMPLEX",
  "OPTIMIZATION_METHOD_NOT_APPLICABLE"
};

/// Interpolation method
enum Interpolation_Method {
  BILINEAR=0,
  KEYS_FOURTH,
  // DON'T ADD ANY BELOW MAX
  MAX_INTERPOLATION_METHOD,
  NO_SUCH_INTERPOLATION_METHOD
};

const static char * interpolationMethodStrings[] = {
  "BILINEAR",
  "KEYS_FOURTH"
};

/// Correlation routine (determines how the correlation steps are executed).
/// Can be customized for a particular application
enum Correlation_Routine {
  GENERIC_ROUTINE=0,
  SL_ROUTINE,
  SUBSET_EVOLUTION_ROUTINE,
  CORRELATION_ROUTINE_NOT_APPLICABLE,
  // DON'T ADD ANY BELOW MAX
  MAX_CORRELATION_ROUTINE,
  NO_SUCH_CORRELATION_ROUTINE
};

const static char * correlationRoutineStrings[] = {
  "GENERIC_ROUTINE",
  "SL_ROUTINE",
  "SUBSET_EVOLUTION_ROUTINE",
  "CORRELATION_ROUTINE_NOT_APPLICABLE"
};

/// Output file type
enum Output_File_Type {
  TEXT_FILE=0,
  // DON'T ADD ANY BELOW MAX
  MAX_OUTPUT_FILE_TYPE,
  NO_SUCH_OUTPUT_FILE_TYPE
};

const static char * outputFileTypeStrings[] = {
  "TEXT_FILE"
};

/// Status flags
enum Status_Flag{
  // 0
  CORRELATION_SUCCESSFUL=0,
  // 1
  INITIALIZE_USING_PREVIOUS_FRAME_SUCCESSFUL,
  // 2
  INITIALIZE_USING_CONNECTED_SUBSET_VALUE_SUCCESSFUL,
  // 3
  INITIALIZE_USING_NEIGHBOR_VALUE_SUCCESSFUL,
  // 4
  INITIALIZE_SUCCESSFUL,
  // 5
  INITIALIZE_FAILED,
  // 6
  SEARCH_SUCCESSFUL,
  // 7
  SEARCH_FAILED,
  // 8
  CORRELATION_FAILED,
  // 9
  SUBSET_CONSTRUCTION_FAILED,
  // 10
  LINEAR_SOLVE_FAILED,
  // 11
  MAX_ITERATIONS_REACHED,
  // 12
  INITIALIZE_FAILED_BY_EXCEPTION,
  // 13
  SEARCH_FAILED_BY_EXCEPTION,
  // 14
  CORRELATION_FAILED_BY_EXCEPTION,
  // 15
  CORRELATION_BY_AVERAGING_CONNECTED_VALUES,
  // 16
  JUMP_TOLERANCE_EXCEEDED,
  // 17
  ZERO_HESSIAN_DETERMINANT,
  // 18
  SEARCH_USING_PREVIOUS_STEP_SUCCESSFUL,
  // 19
  LINEARIZED_GAMMA_OUT_OF_BOUNDS,
  // 20
  NAN_IN_HESSIAN_OR_RESIDUAL,
  // 21
  HESSIAN_SINGULAR,
  // 22
  SKIPPED_FRAME_DUE_TO_HIGH_GAMMA,
  // 23
  RESET_REF_SUBSET_DUE_TO_HIGH_GAMMA,
  // 24
  MAX_GLOBAL_ITERATIONS_REACHED_IN_EVOLUTION_LOOP,
  // 25
  FAILURE_DUE_TO_TOO_MANY_RESTARTS,
  // 26
  FRAME_SKIPPED,
  // DON'T ADD ANY BELOW MAX
  MAX_STATUS_FLAG,
  NO_SUCH_STATUS_FLAG
};

const static char * statusFlagStrings[] = {
  "CORRELATION_SUCCESSFUL",
  "INITIALIZE_USING_PREVIOUS_STEP_SUCCESSFUL",
  "INITIALIZE_USING_CONNECTED_SUBSET_VALUE_SUCCESSFUL",
  "INITIALIZE_USING_NEIGHBOR_VALUE_SUCCESSFUL",
  "INITIALIZE_SUCCESSFUL",
  "INITIALIZE_FAILED",
  "SEARCH_SUCCESSFUL",
  "SEARCH_FAILED",
  "CORRELATION_FAILED",
  "SUBSET_CONSTRUCTION_FAILED",
  "LINEAR_SOLVE_FAILED",
  "MAX_ITERATIONS_REACHED",
  "INITIALIZE_FAILED_BY_EXCEPTION",
  "SEARCH_FAILED_BY_EXCEPTION",
  "CORRELATION_FAILED_BY_EXCEPTION",
  "CORRELATION"
  "_BY_AVERAGING_CONNECTED_VALUES",
  "JUMP_TOLERANCE_EXCEEDED",
  "ZERO_HESSIAN_DETERMINANT",
  "SEARCH_USING_PREVIOUS_STEP_SUCCESSFUL",
  "LINEARIZED_GAMMA_OUT_OF_BOUNDS",
  "NAN_IN_HESSIAN_OR_RESIDUAL",
  "HESSIAN_SINGULAR",
  "SKIPPED_FRAME_DUE_TO_HIGH_GAMMA",
  "RESET_REF_SUBSET_DUE_TO_HIGH_GAMMA",
  "MAX_GLOBAL_ITERATIONS_REACHED_IN_EVOLUTION_LOOP",
  "FAILURE_DUE_TO_TOO_MANY_RESTARTS",
  "FRAME_SKIPPED"
};

/// The type of correlation parameter, used for creating template input files
enum Correlation_Parameter_Type{
  STRING_PARAM=0,
  PARAM_PARAM, // parameter that is another parameter list
  REAL_PARAM,
  SIZE_PARAM,
  BOOL_PARAM
};

/// \class DICe::Correlation_Parameter
/// \brief Simple struct to hold information about correlation parameters
struct Correlation_Parameter {
  /// \brief Only constructor with several optional arguments
  /// \param name The string name of the correlation parameter
  /// \param type Defines if this is a bool, string, integer value, etc.
  /// \param expose_to_user Signifies that this should be included when template input files are made
  /// \param desc Correlation parameter description
  /// \param stringNames Pointer to the array of string names for this parameter if this is a string parameter, otherwise null pointer
  /// \param size The number of available options for this correlation parameter
  Correlation_Parameter(const std::string & name, const Correlation_Parameter_Type & type,
    const bool expose_to_user=true,
    const std::string & desc="No description",
    const char ** stringNames=0,
    const int_t size=0){
    name_ = name;
    type_ = type;
    desc_ = desc;
    stringNamePtr_ = stringNames;
    size_ = size;
    expose_to_user_ = expose_to_user;
  }
  /// Name of the parameter (what will be used from the input file if specified)
  std::string name_;
  /// Type of parameter (bool, size, real, string)
  Correlation_Parameter_Type type_;
  /// Pointer to the string names of all the options
  const char ** stringNamePtr_;
  /// The number of potential options
  int_t size_;
  /// Short description of the correlation parameter
  std::string desc_;
  /// Determines if this param shows up in the template input files exposed to the user
  bool expose_to_user_;
};

/// Correlation parameter and properties
const Correlation_Parameter obstruction_buffer_size_param(obstruction_buffer_size,
  SIZE_PARAM,
  true,
  "Specifies the size of the buffer to add around an obstructing object (essentially makes the obstruction larger).");
/// Correlation parameter and properties
const Correlation_Parameter pixel_integration_order_param(pixel_integration_order,
  SIZE_PARAM,
  true,
  "Specifies the integration order to use (number of subdivisions for each pixel). Used only in the constrained optimization formulation.");

/// Correlation parameter and properties
const Correlation_Parameter obstruction_skin_factor_param(obstruction_skin_factor,
  REAL_PARAM,
  true,
  "Stretches the obstruction subsets to make them larger (factor > 1.0) or smaller (factor < 1.0) than they actually are.");

/// Correlation parameter and properties
const Correlation_Parameter output_delimiter_param(output_delimiter,
  STRING_PARAM,
  true,
  "Delimeter to separate column values in output files, (comma or space, etc.)");
/// Correlation parameter and properties
const Correlation_Parameter omit_output_row_id_param(omit_output_row_id,
  BOOL_PARAM,
  true,
  "True if the row id should be omitted from the output (column zero is skipped)");
/// Correlation parameter and properties
const Correlation_Parameter output_spec_param(output_spec,
  STRING_PARAM,
  false, // turned off because this one is manually added to the template output files
  "Determines what output to write and in what order");
/// Correlation parameter and properties
const Correlation_Parameter correlation_routine_param(correlation_routine,
  STRING_PARAM,
  true,
  "Determines the correlation order of execution (see DICe::Schema)",
  correlationRoutineStrings,
  MAX_CORRELATION_ROUTINE);
/// Correlation parameter and properties
const Correlation_Parameter interpolation_method_param(interpolation_method,
  STRING_PARAM,
  true,
  "Determines which interpolation method to use (can also affect the image gradients)",
  interpolationMethodStrings,
  MAX_INTERPOLATION_METHOD);
/// Correlation parameter and properties
const Correlation_Parameter initialization_method_param(initialization_method,
  STRING_PARAM,
  true,
  "Determines how solution values are initialized for each frame",
  initializationMethodStrings,
  MAX_INITIALIZATION_METHOD);
/// Correlation parameter and properties
const Correlation_Parameter optimization_method_param(optimization_method,
  STRING_PARAM,
  true,
  "Determines if gradient based (fast, but not as robust) or simplex based (no gradients needed, but requires more iterations) optimization algorithm will be used",
  optimizationMethodStrings,
  MAX_OPTIMIZATION_METHOD);
/// Correlation parameter and properties
const Correlation_Parameter projection_method_param(projection_method,
  STRING_PARAM,
  true,
  "Determines how solution values from previous frames are used to predict the current solution",
  projectionMethodStrings,
  MAX_PROJECTION_METHOD);
/// Correlation parameter and properties
const Correlation_Parameter enable_translation_param(enable_translation,
  BOOL_PARAM,
  true,
  "Enables the translation shape function degrees of freedom (u and v)");
/// Correlation parameter and properties
const Correlation_Parameter enable_rotation_param(enable_rotation,
  BOOL_PARAM,
  true,
  "Enables the rotation shape function degree of freedom (theta)");
/// Correlation parameter and properties
const Correlation_Parameter enable_normal_strain_param(enable_normal_strain,
  BOOL_PARAM,
  true,
  "Enables the normal strain shape function degrees of freedom (epsilon_x and epsilon_y)");
/// Correlation parameter and properties
const Correlation_Parameter enable_shear_strain_param(enable_shear_strain,
  BOOL_PARAM,
  true,
  "Enables the shear strain shape function defree of freedom (gamma_xy = gamma_yx)");
/// Correlation parameter and properties
const Correlation_Parameter search_window_size_factor_param(search_window_size_factor,
  REAL_PARAM,
  true,
  "Determines how large the search window is compared to a subset");
/// Correlation parameter and properties
const Correlation_Parameter search_window_skip_param(search_window_skip,
  SIZE_PARAM,
  true,
  "Determines how many pixels to skip while traversing the search window");
/// Correlation parameter and properties
const Correlation_Parameter max_evolution_iterations_param(max_evolution_iterations,SIZE_PARAM,true,"Maximum evolution iterations to use (only valid for subset_evolution_routine)");
/// Correlation parameter and properties
const Correlation_Parameter max_solver_iterations_fast_param(max_solver_iterations_fast,SIZE_PARAM);
/// Correlation parameter and properties
const Correlation_Parameter max_solver_iterations_robust_param(max_solver_iterations_robust,SIZE_PARAM);
/// Correlation parameter and properties
const Correlation_Parameter fast_solver_tolerance_param(fast_solver_tolerance,REAL_PARAM);
/// Correlation parameter and properties
const Correlation_Parameter robust_solver_tolerance_param(robust_solver_tolerance,REAL_PARAM);
/// Correlation parameter and properties
const Correlation_Parameter skip_solve_gamma_threshold_param(skip_solve_gamma_threshold,REAL_PARAM,true,
  "If the gamma evaluation for the initial deformation guess is below this value, the solve is skipped because"
  " the match is already good enough");
/// Correlation parameter and properties
const Correlation_Parameter pixel_size_in_mm_param(pixel_size_in_mm,
  REAL_PARAM,
  true,
  "The spatial size of one pixel (1 pixel is equivalent to ? mm");
/// Correlation parameter and properties
const Correlation_Parameter disp_jump_tol_param(disp_jump_tol,
  REAL_PARAM,
  true,
  "Displacement solutions greater than this from the previous frame will be rejected as unsuccessful");
/// Correlation parameter and properties
const Correlation_Parameter theta_jump_tol_param(theta_jump_tol,
  REAL_PARAM,
  true,
  "Rotation solutions greater than this from the previous frame will be rejected as unsuccessful");
/// Correlation parameter and properties
const Correlation_Parameter robust_delta_disp_param(robust_delta_disp,
  REAL_PARAM,
  true,
  "Variation on initial displacement guess used to construct simplex");
/// Correlation parameter and properties
const Correlation_Parameter robust_delta_theta_param(robust_delta_theta,
  REAL_PARAM,
  true,
  "Variation on initial rotation guess used to construct simplex");
/// Correlation parameter and properties
const Correlation_Parameter output_deformed_subset_images_param(output_deformed_subset_images,
  BOOL_PARAM,
  true,
  "EXPERIMENTAL Write images that show the deformed position of the subsets (Currently only available for SL_ROUTINE correlation_routine, not GENERIC)");
/// Correlation parameter and properties
const Correlation_Parameter output_deformed_subset_intensity_images_param(output_deformed_subset_intensity_images,
  BOOL_PARAM,
  true,
  "EXPERIMENTAL Write images that show the intensity profile of the deformed subsets");
/// Correlation parameter and properties
const Correlation_Parameter output_evolved_subset_images_param(output_evolved_subset_images,
  BOOL_PARAM,
  true,
  "EXPERIMENTAL Write images that show the reference subset as its intensity profile evolves");
/// Correlation parameter and properties
const Correlation_Parameter use_subset_evolution_param(use_subset_evolution,
  BOOL_PARAM,
  true,
  "EXPERIMENTAL Used to evolve subsets that are initially obscured (Currently only available for SL_ROUTINE correlation routine, not GENERIC)");
/// Correlation parameter and properties
const Correlation_Parameter use_sl_default_params_param(use_sl_default_params,
  BOOL_PARAM,
  true,
  "Use the SL default parameters instead of the typical dice defaults (Not commonly used).");
/// Correlation parameter and properties
const Correlation_Parameter update_obstructed_pixels_each_iteration_param(update_obstructed_pixels_each_iteration,
  BOOL_PARAM,
  true,
  "Rather than update the obstructed pixels only at the start of each frame, do so at each iteration in the analysis.");
/// Correlation parameter and properties
const Correlation_Parameter normalize_gamma_with_active_pixels_param(normalize_gamma_with_active_pixels,
  BOOL_PARAM,
  true,
  "True if the computed gamma value (or matching quality) will be normalized by the number of active pixels.");
/// Correlation parameter and properties
const Correlation_Parameter use_global_dic_param(use_global_dic,
  BOOL_PARAM,
  false,
  "True if the global method should be used rather than subset or local DIC.");
/// Correlation parameter and properties
const Correlation_Parameter use_constrained_opt_dic_param(use_constrained_opt_dic,
  BOOL_PARAM,
  false,
  "True if the constrained optimization method should be used rather than subset or local DIC.");
/// Correlation parameter and properties
const Correlation_Parameter use_integrated_dic_param(use_integrated_dic,
  BOOL_PARAM,
  false,
  "True if the integrated DIC algorithms should be used rather than subset or local DIC.");
/// Correlation parameter and properties
const Correlation_Parameter use_hvm_stabilization_param(use_hvm_stabilization,
  BOOL_PARAM,
  false,
  "True if the global method should be use HVM stabilization.");
/// Correlation parameter and properties
const Correlation_Parameter use_objective_regularization_param(use_objective_regularization,
  BOOL_PARAM,
  false,
  "True if regularization terms should be added to the objective minimization process (similar to damping).");

// These are not exposed automatically to the user (they are internal params used by the schema and image classes)

/// Correlation parameter and properties
const Correlation_Parameter compute_ref_gradients_param(compute_ref_gradients,
  BOOL_PARAM,
  false,
  "Compute image gradients for the reference frame");
/// Correlation parameter and properties
const Correlation_Parameter gauss_filter_images_param(gauss_filter_images,
  BOOL_PARAM,
  false,
  "Filter the images using a 7 point gauss filter (eliminates high frequnecy content)");
/// Correlation parameter and properties
const Correlation_Parameter compute_def_gradients_param(compute_def_gradients,
  BOOL_PARAM,
  false,
  "Compute image gradients for the deformed image of the current frame");
/// Correlation parameter and properties
const Correlation_Parameter compute_image_gradients_param(compute_image_gradients,
  BOOL_PARAM,
  false,
  "Compute image gradients");

// TODO don't forget to update this when adding a new one
/// The total number of valid correlation parameters
const int_t num_valid_correlation_params = 42;
/// Vector of valid parameter names
const Correlation_Parameter valid_correlation_params[num_valid_correlation_params] = {
  correlation_routine_param,
  interpolation_method_param,
  initialization_method_param,
  optimization_method_param,
  projection_method_param,
  compute_ref_gradients_param,
  compute_def_gradients_param,
  compute_image_gradients_param,
  gauss_filter_images_param,
  enable_translation_param,
  enable_rotation_param,
  enable_normal_strain_param,
  enable_shear_strain_param,
  search_window_size_factor_param,
  search_window_skip_param,
  max_evolution_iterations_param,
  max_solver_iterations_fast_param,
  max_solver_iterations_robust_param,
  fast_solver_tolerance_param,
  robust_solver_tolerance_param,
  skip_solve_gamma_threshold_param,
  disp_jump_tol_param,
  theta_jump_tol_param,
  robust_delta_disp_param,
  robust_delta_theta_param,
  output_deformed_subset_images_param,
  output_deformed_subset_intensity_images_param,
  output_evolved_subset_images_param,
  use_subset_evolution_param,
  output_spec_param,
  output_delimiter_param,
  omit_output_row_id_param,
  obstruction_buffer_size_param,
  obstruction_skin_factor_param,
  use_sl_default_params_param,
  update_obstructed_pixels_each_iteration_param,
  normalize_gamma_with_active_pixels_param,
  use_global_dic_param,
  use_constrained_opt_dic_param,
  use_integrated_dic_param,
  use_hvm_stabilization_param,
  use_objective_regularization_param,
  pixel_integration_order_param
};

// TODO don't forget to update this when adding a new one
/// The total number of valid correlation parameters
const int_t num_valid_global_correlation_params = 11;
/// Vector of valid parameter names
const Correlation_Parameter valid_global_correlation_params[num_valid_global_correlation_params] = {
  use_global_dic_param,
  use_constrained_opt_dic_param,
  use_integrated_dic_param,
  interpolation_method_param,
  gauss_filter_images_param,
  max_solver_iterations_fast_param,
  fast_solver_tolerance_param,
  output_spec_param,
  output_delimiter_param,
  omit_output_row_id_param,
  use_hvm_stabilization_param
};

/// The total number of valid correlation params
const int_t num_valid_constrained_opt_correlation_params = 6;
/// Vector of valid parameter names
const Correlation_Parameter valid_constrained_opt_correlation_params[num_valid_constrained_opt_correlation_params] = {
  use_global_dic_param,
  use_constrained_opt_dic_param,
  use_integrated_dic_param,
  interpolation_method_param,
  pixel_integration_order_param,
  max_solver_iterations_fast_param
};

/// The total number of valid correlation params
const int_t num_valid_integrated_correlation_params = 11;
/// Vector of valid parameter names
const Correlation_Parameter valid_integrated_correlation_params[num_valid_integrated_correlation_params] = {
  use_global_dic_param,
  use_constrained_opt_dic_param,
  use_integrated_dic_param,
  interpolation_method_param,
  max_solver_iterations_robust_param,
  robust_solver_tolerance_param,
  output_deformed_subset_images_param,
  output_deformed_subset_intensity_images_param,
  output_evolved_subset_images_param,
  correlation_routine_param,
  optimization_method_param
};

} // end DICe namespace

#endif
