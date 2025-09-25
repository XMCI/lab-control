// *************** gsense4040control.h - function prototypes scmos camera *******************

/**
 * \file gsense4040control.h
 *  Function Prototypes for GSense4040.
 *
 *  Header file containing function prototypes and documentation for GSense4040 camera.
 *  Version: 13.5.17.0
 */

///\cond

#ifndef _PSL_VHR_H_
#define _PSL_VHR_H_

#define i32 signed long
#define ui32 unsigned long

#define MICROSECONDS 0
#define MILLISECONDS 1
#define SECONDS 2

#ifdef MAKE_A_DLL
#define LINKDLL __declspec(dllexport)
#else
#define LINKDLL __declspec(dllimport)
#endif

///\endcond

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Function to get driver version_str.
	 *
	 * \return char* pointer to null terminated string
	 */
	LINKDLL const char *PS_GetDriverVersion();

	/**
	 * Function to set IP and MAC addresses.
	 * 
	 * <b> Example: <code>PSL_VHR_select_IPORT_device("00-11-1c-00-60-3d","[192.168.101.28]");</code></b>
	 * 
	 * \note ONLY for systems using an NTX interface, specify the MAC address of an existing networked\n
	 * NTX device and the IP address to be assigned to it. This function should be called\n
	 * before PSL_VHR_Open(), and will only have an effect on NTX based cameras.
	 * 
	 * \param MACaddress fill in MAC address
	 * \param IPaddress fill in IP address
	 */
	LINKDLL	void PSL_VHR_select_IPORT_device(char *MACaddress, char *IPaddress);

	/**
	 * Main function to start PS cameras.
	 * Main function to initialize, connect, configure and start up PS cameras and resources needed for standard operation.\n
	 *
	 * \param PSL_camera_files_path path to camera calibration files Dir
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_Open(char *PSL_camera_files_path);

	/**
	 * Opens map file and loads it to driver memory.
	 *
	 * \param mapfile path to map file (file included)
	 * \return true = success \n
	 *         false = failure (map file missing or header information miss-match) \n
	 */
	LINKDLL bool PSL_VHR_open_map(char *mapfile);

	/**
	 * Returns MaxWidth of sensor independent on bin mode.
	 *
	 * \return iMaxWidth \n
	 *		   0 - if system is not initialized / ready \n
	 */
	LINKDLL long signed	PSL_VHR_get_maximum_width(void);

	/**
	 * Returns MaxHeight of sensor independent on bin mode.
	 *
	 * \return iMaxHeight \n
	 *		   0 - if system is not initialized / ready \n
	 */
	LINKDLL long signed	PSL_VHR_get_maximum_height(void);

	/**
	 * Reads the sensor temperature in degrees Celsius.
	 *
	 * \return value as int
	 */
	LINKDLL int PSL_VHR_read_CCD_temperature(void);

	/**
	 * Closes system and frees up every resource.
	 *
	 * \return true = success \n
	 *         false = failure (SystemNotReady)
	 */
	LINKDLL bool PSL_VHR_Close(void);

	/**
	 * Enables image streaming on GEV interface.
	 * Other functions use this automatically.
	 * \note ONLY for cameras with an NTX interface - enable continuous output of images from camera to PC.
	 *
	 * \param bEnable true or false
	 */
	LINKDLL void PSL_VHR_enable_image_streaming(bool bEnable);

	/**
	 * Start acquisition to GEV stream.
	 * \note ONLY for cameras with an NTX interface - to be used AFTER having called \n
	 * PSL_VHR_enable_image_streaming(true) in order to actually start streaming images. 
	 *
	 * \return true = success \n
	 *         false = failure (GEV stream failed to Start) \n
	 */
	LINKDLL bool PSL_VHR_start_acquisition(void);

	/**
	 * Enables peltier cooling in camera if available.
	 *
	 * \param bEnabled true = cooling on \n
	 *		           false = cooling off 
	 * 
	 * \return true = success \n
	 *         false = failure (failed to send enable to camera) \n
	 */
	LINKDLL bool PSL_VHR_enable_cooling(bool bEnabled);

	/**
	 * Reads peltier cooling state from camera.
	 *
	 * \return true = enabled \n
	 *         false = failure or disabled (failed to read from camera) \n
	 */
	LINKDLL bool PSL_VHR_cooling_is_enabled(void);

	/**
	 * Sets operating gain mode of camera.
	 * Possible values:
	 * 
	 * Integer | Gain Mode
	 * --------|-----------
	 * 0	   | low gain
	 * 5	   | higher low gain
	 * 6	   | lower high gain
	 * 7	   | high gain
	 * 10	   | mixed gains (low gain(0) and high gain(7) fixed in camera)
	 *
	 * \note Forces driver to reload calibration files as previous ones will become invalid.
	 * \note Accepts only values 1 to 10, if value is nit in above list it will default to low gain(0).
	 *
	 * \param iMode (as above)
	 * \return true = success \n
	 *         false = Invalid or failure (failed to set camera in specified gain mode) \n
	 */
	LINKDLL bool PSL_VHR_set_gain_mode(int iMode);

	/**
	 * Returns current operating gain mode of driver.
	 * For gain modes and values please see PSL_VHR_set_gain_mode() description.
	 *
	 * \return iCurrentGainMode value
	 */
	LINKDLL int PSL_VHR_get_gain_mode(void);

	/**
	 * Sets exposure time of camera in microseconds.
	 *
	 * \param time_in_microsecs in range [1 to 2,147,483,647] (32bit integer)
	 * \return true = success \n
	 *         false = failure (SystemNotReady or failed to send to camera) \n
	 */
	LINKDLL bool PSL_VHR_set_exposure(int time_in_microsecs);

	/**
	 * Sets trigger mode of which can be one of:
	 * 
	 * Integer | Trigger Mode
	 * --------|------------
	 * 0	   | free running
	 * 1	   | SW triggered
	 * 2	   | HW falling edge
	 * 6	   | HW rising edge
	 *
	 * \note These features/modes are checked and tested on a per camera basis,\n
	 * to see test results please refer to the Test Summary document supplied with the camera.
	 * 
	 * \param trigger_mode (as above)
	 * \return true = success \n
	 *         false = Invalid or failure (failed to set camera in specified trigger mode) \n
	 */
	LINKDLL bool PSL_VHR_set_trigger_mode(int trigger_mode);

	/**
	 * Returns current operating trigger mode of driver.
	 * For trigger modes and values please see PSL_VHR_set_trigger_mode() description.
	 *
	 * \return iTriggerMode value
	 */
	LINKDLL int PSL_VHR_get_trigger_mode();

	/**
	 * Sets subarea coordinates and binning in Hardware.
	 * ROI ranges are: \n
	 * 0 to MaxWidth-1 ((4096/xBin)-1) for left and right \n
	 * 0 to MaxHeight-1 ((4096/yBin)-1) for top and bottom \n
	 * x_Bin and y_Bin values in range 1-2
	 * 
	 * \note If larger ROI is specified (e.g in case of Bin2 mode) than sensor is capable to produce \n
	 * then ROI will be adjusted to maximum allowed area. \n
	 * \n
	 * For example full area can be specified using the following \n
	 * coordinate pairs (x, y) to specify the (top,left) and (bottom,right) corners of the imaging area: \n
	 * PSL_VHR_set_sub_area_coordinates_and_binning(0, 4095, 0, 4095, 1, 1);
	 * 
	 * \note ROI coordinates are recalculated inside this function to ensure pixel quantization is retained. \n
	 * After calling this function query and update your acquisition area to new values by calling \n
	 * PSL_VHR_get_actual_sub_area_coordinates(i32 *left, i32 *right, i32 *top, i32 *bottom); function. 
	 * 
	 * \param left   range 0 to right-1
	 * \param right  range left+1 to MaxWidth-1
	 * \param top    range 0 to bottom-1
	 * \param bottom range top+1 to MaxHeight-1
	 * \param x_Bin  1 or 2
	 * \param y_Bin  1 or 2
	 * \return true = success \n
	 *         false = Invalid or failure (failed to set camera in specified gain mode) \n
	 */
	LINKDLL bool PSL_VHR_set_sub_area_coordinates_and_binning(i32 left, i32 right, i32 top, i32 bottom, i32 x_Bin, i32 y_Bin);

	/**
	 * Sets subarea coordinates in Hardware.
	 * ROI ranges are: \n
	 * 0 to MaxWidth-1 ((4096/xBin)-1) for left and right \n
	 * 0 to MaxHeight-1 ((4096/yBin)-1) for top and bottom.
	 * 
	 * \note If larger ROI is specified (e.g in case of Bin2 mode) than sensor is capable to produce \n
	 * then ROI will be adjusted to maximum allowed area. \n
	 * \n
	 * For example full area can be specified using the following \n
	 * coordinate pairs (x, y) to specify the (top,left) and (bottom,right) corners of the imaging area: \n
	 * PSL_VHR_set_sub_area_coordinates(0, 4095, 0, 4096);
	 * 
	 * \note ROI coordinates are recalculated inside this function to ensure pixel quantization is retained. \n
	 * After calling this function query and update your acquisition area to new values by calling \n
	 * PSL_VHR_get_actual_sub_area_coordinates(i32 *left, i32 *right, i32 *top, i32 *bottom); function.
	 * 
	 * \param left   range 0 to right-1
	 * \param right  range left+1 to MaxWidth-1
	 * \param top    range 0 to bottom-1
	 * \param bottom range top+1 to MaxHeight-1
	 * \return true = success \n
	 *         false = Invalid or failure (failed to set camera in specified mode) \n
	 */
	LINKDLL bool PSL_VHR_set_sub_area_coordinates(i32 left, i32 right, i32 top, i32 bottom);

	/**
	 * Returns currently specified subarea coordinates (dependent on binning).
	 * Always update ROI coordinates with this function after a subarea set function was called \n
	 * as subarea may be different to those specified because of quantization due to hardware restrictions! \n
	 * Call example: PSL_VHR_get_actual_sub_area_coordinates(&left, &right, &top, &bottom);
	 *
	 * \param left   (out)ROI coordinate
	 * \param right  (out)ROI coordinate
	 * \param top    (out)ROI coordinate
	 * \param bottom (out)ROI coordinate
	 */
	LINKDLL void PSL_VHR_get_actual_sub_area_coordinates(i32 *left, i32 *right, i32 *top, i32 *bottom);

	/**
	 * Returns currently specified subarea coordinates (independent on binning).
	 * Always update ROI coordinates with this function after a subarea set function was called \n
	 * as subarea may be different to those specified because of quantization due to hardware restrictions! \n
	 * Call example: PSL_VHR_get_absolute_sub_area_coordinates(&left, &right, &top, &bottom);
	 * 
	 * \param left   (out)ROI coordinate
	 * \param right  (out)ROI coordinate
	 * \param top    (out)ROI coordinate
	 * \param bottom (out)ROI coordinate
	*/
	LINKDLL void PSL_VHR_get_absolute_sub_area_coordinates(i32 *left, i32 *right, i32 *top, i32 *bottom);

	/**
	 * Enables or disables Offset Subtraction SW post snap correction.
	 * Call before snap and post snap processing to take effect.
	 *
	 * \param bEnabled true or false
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_enable_offset_subtraction(bool bEnabled);	// offset correction

	/**
	 * Enables or disables Bright Corner Subtraction SW post snap correction.
	 * Call before snap and post snap processing to take effect.
	 *
	 * \param bEnabled true or false
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_enable_bright_corner_subtraction(bool bEnabled); // bright corner subtraction

	/**
	 * Enables or disables Bright Pixel SW post snap correction.
	 * Call before snap and post snap processing to take effect.
	 *
	 * \param bEnabled true or false
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_enable_bright_pixel_correction(bool bEnabled);	// bright pixel correction

	/**
	 * Enables or disables Flat Field SW post snap correction.
	 * Call before snap and post snap processing to take effect.
	 *
	 * \param bEnabled true or false
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_enable_flat_field_correction(bool bEnabled);	// flat correction

	/**
	 * Enables or disables Sharpening SW post snap correction.
	 * Call before snap and post snap processing to take effect.
	 *
	 * \param bEnabled true or false
	 */
	LINKDLL	void PSL_VHR_enable_sharpening(bool bEnabled); // sharpening

	/**
	 * Generates Flat Field correction file.
	 * Replaces flat_<gainmode>.flf and flat_<gainmode>_bin2.flf files in PSL_camera_files \n
	 * folder with newly generated ones according your current operation mode (gain mode and binning).
	 * \note Make sure to back up your original files if calling this function!
	 *
	 * \param numtoaverage number of images to average to generate new correction file, range 1 to 256.
	 * \return true = success \n
	 *         false = failure (failed generate or write file) \n
	 */
	LINKDLL bool PSL_VHR_generate_flat_field_image(int numtoaverage);

	/**
	 * Acquisition new image into memory location outside driver.
	 * Optional function to provide a memory location where driver memcpys new image data.
	 * 
	 * \warning This function saves and additional memcpy operation but use with care!! \n
	 * Make sure that the allocated memory space is large enough for the image being acquisition-ed! \n
	 * !!!Otherwise may run into Memory access violation!!!
	 *
	 * \param ptr_buffer pointer to the start of destination memory location.
	 * \return true = success \n
	 *         false = failure (in case ptr_buffer==NULL - attempted safety check) \n
	 */
	LINKDLL bool PSL_VHR_set_customers_buffer(unsigned short *ptr_buffer);

	/**
	 * Initiate acquisition of one single image.
	 * \note Reloads calibration files before sending trigger in case \n
	 * any camera setup changes were recorded (gain mode, trigger mode, binning). \n
	 *
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_Snap_and_return(void);

	/**
	 * Returns status of current snap request.
	 * If image is acquisition-ed copies image data from transfer interface to memory location \n
	 * initialized in driver or to location set up and shared by customer via \n
	 * PSL_VHR_set_customers_buffer(); function.
	 * 
	 * \note Query this function from a while loop after PSL_VHR_Snap_and_return(); was called.
	 *
	 * \return true = finished \n
	 *         false = still in progress \n
	 */
	LINKDLL bool PSL_VHR_Get_snap_status(void);

	/**
	 * Function to abort snap process.
	 *
	 * \return true = success\n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_abort_snap(void);

	/**
	 * Snap multiple images and average them.
	 * Snap nbr_images_to_avg with delay_ms between snaps and average output. \n
	 * To get averaged image output call PSL_VHR_get_avg_accumulation_image_pointer() function. \n
	 * Post processing is run on every image before averaging.
	 * 
	 * \note Not intended to be used instead of PSL_VHR_Snap_and_return()
	 *
	 * \param nbr_images_to_avg number of images to average together
	 * \param delay_ms delay between consecutive snaps
	 * \return true = finished \n
	 *         false = still in progress \n
	 */
	LINKDLL bool PSL_VHR_snap_avg_accumulation(unsigned long nbr_images_to_avg, unsigned long delay_ms);

	/**
	 * Function to get pointer to memory location of image (stored in driver).
	 * Same memory location can be used for post processing in case acquisition-ed images.
	 * 
	 * \note Call after PSL_VHR_Get_snap_status()==true per every snap request in order \n
	 * to get a pointer to the current image data.
	 *
	 * \return pointer to the memory locations storing image.
	 */
	LINKDLL unsigned short *PSL_VHR_get_image_pointer(void);

	/**
	 * Function to get pointer to memory location of avg_image (stored in driver).
	 * Call after PSL_VHR_snap_avg_accumulation()==true per every request in order \n
	 * to get a pointer to the avg_image data.
	 *
	 * \return pointer to the memory locations storing avg_image.
	 */
	LINKDLL unsigned short *PSL_VHR_get_avg_accumulation_image_pointer(void);

	/**
	 * Returns current width of subarea image.
	 *
	 * \return iCurrentWidth
	 */
	LINKDLL long signed PSL_VHR_get_width(void);

	/**
	 * Returns current height of subarea image.
	 *
	 * \return iCurrentHeight
	 */
	LINKDLL long signed PSL_VHR_get_height(void);

	/**
	 * Query if sensor is set up in color mode.
	 *
	 * \return true = Color sensor \n
	 *         false = Gray scale only \n
	 */
	LINKDLL bool PSL_VHR_Is_Colour_Sensor(void);

	/**
	 * Function to post process image after acquisition.
	 * This function is used to run software corrections on the image after every snap request. \n
	 * The operation of post processing is heavily dependent on: \n
	 *   1. CURRENT Camera parameters - such as Exposure, Gain Mode, Trigger Mode, etc (aka cam_runtime parameters).
	 *   2. Enabled post correction processes - Offset Correction, Bright Corner, Flat Fielding, Bright Pixel, Sharpening.
	 *   3. Camera calibration - all files found under PSL_camera_files directory (supplied with every individual camera).
	 * 
	 * If any of the above parameters have changed between the Snap and the Post Processing call it is highly advised to Snap a new image \n
	 * to ensure that Post Processing will work with the correct cam_runtime parameters and correction data. \n
	 * 
	 * Main responsibilities of this function: \n
	 *   1. Fixed Pattern Correction (Default if set by PS calibration).
	 *   2. Structure Correction (Default if set by PS calibration).
	 *   3. Offset Correction (Enabled by PSL_VHR_enable_offset_subtraction() function).
	 *   4. Bright Corner Correction (Enabled by PSL_VHR_enable_bright_corner_subtraction() function).
	 *   5. Bright Pixel Static Correction (Enabled by PSL_VHR_enable_bright_pixel_correction() function).
	 *   6. Flat Field Correction (Enabled by PSL_VHR_enable_flat_field_correction() function).
	 *   7. Bright Pixel Kernel Correction (Enabled by PSL_VHR_enable_bright_pixel_correction() function).
	 *   8. Image Sharpening (Enabled by PSL_VHR_enable_sharpening() function, useful in case Combining modes).
	 *   9. Horizontal Flip (Default if set by PS calibration).
	 *
	 * \param pImage pointer to the start of the memory location where image is located \n- can be the pointer returned by PSL_VHR_get_image_pointer()
	 * \return pointer to start of memory location where post processed image is stored.
	 */
	LINKDLL bool PSL_VHR_apply_post_snap_processing(unsigned short *pImage);

	/**
	 * Function to remap image.
	 * Remaps the image data in orig_image and returns a pointer to the remapped image. \n
	 * The dimensions of the remapped image are updated in image_width and image_height parameters. \n
	 * Use PSL_VHR_open_map(char *mapfile) function to load map file.
	 * 
	 * \note PSL_VHR_remap_image() must be called before PSL_VHR_software_bin_image(), since \n
	 * the map coordinates relate to the raw image buffer (NOT the software binned buffer).
	 *
	 * \param orig_image pointer to start of original image memory location
	 * \param image_width (in) original image width, (out) after remapping image_width will be updated
	 * \param image_height (in) original image height (out) after remapping image_height will be updated
	 * \param bSmoothingEnabled boolean to enable Smoothed mapping.
	 * \param bClippingEnabled boolean to enable Clipped mapping.
	 * \return pointer to start of remapped image memory location
	 */
	LINKDLL unsigned short *PSL_VHR_remap_image(unsigned short *orig_image, int *image_width, int *image_height, bool bSmoothingEnabled, bool bClippingEnabled);

	/**
	 * Function to software bin an image.
	 * Software bins image buffer pointed to by orig_image, whose dimensions are image_width*image_height pixels \n
	 * The binned image is left in orig_image, dimensions are updated in image_width and image_height parameters.
	 *
	 * \param orig_image pointer to start of original image memory location
	 * \param image_width (in) original image width, (out) after binning image_width will be updated
	 * \param image_height (in) original image height (out) after binning image_height will be updated
	 * \param xbinning Horizontal binning value.
	 * \param ybinning Vertical binning value.
	 */
	LINKDLL void PSL_VHR_software_bin_image(unsigned short *orig_image, int *image_width, int *image_height, int xbinning, int ybinning);

	/**
	 * Function to retrain sensor.
	 *
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL	bool PSL_VHR_perform_training(void);

	/**
	 * Reloads force reloads camera correction files from PSL_camera_files_path directory.
	 *
	 * \return iStatus\n
	 *	0 = success\n
	 *	1 = structure file failed to load or wasn't available (optional)\n
	 *  10 = linearization file failed to load or wasn't available (optional)\n
	 *  100 = offset, bright corner, flat field, bright pixel failed to load\n
	 *  or any combination of above ex 111 would mean all file reads failed.\n
	 */
	LINKDLL int PSL_VHR_force_reload_camera_correction_files();

	/**
	 * Writes the password to access locked in camera features.
	 *
	 * \param psw - Password
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_set_password(unsigned int psw);

	/**
	 * Writes the serial number to camera - PSW Locked.
	 *
	 * \param SN - Serial number
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_set_serial_number(unsigned int SN);

	/**
	 * Reads the serial number of the camera.
	 * If SN not set in camera defaults to 0.
	 *
	 * \return SerialNumber 
	 */
	LINKDLL int PSL_VHR_get_serial_number(void);

	/**
	 * Stores current settings to camera - PSW Locked.
	 */
	LINKDLL void PSL_VHR_save_current_settings_to_camera(void);

	/**
	 * Restores factory settings in camera - PSW Locked.
	 * Power-cycle camera after this operation for new values to take effect.
	 * 
	 * \warning DESTRUCTIVE OPERATION - WILL DELETE SERIAL NUMBER ETC.
	 *
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_restore_default_settings_to_camera(void);

	/**
	 * Sends Software Trigger to camera.
	 *
	 * \return true = success \n
	 *		   false = failure
	 */
	LINKDLL bool PSL_VHR_Generate_sw_trigger(void);

	/**
	 * Query if this is GEV aka eBUS compatible driver.
	 *
	 * \return true = GEV aka eBUS compatible driver \n
	 *         false = Non GEV compatible driver (CameraLink, IPORT) \n
	 */
	LINKDLL bool PSL_VHR_this_is_GEV_version_of_dll(void);

	/**
	 * Sets pixel depth in the camera.
	 * Potential values:
	 *
	 * Integer | Pixel Depth
	 * --------|------------
	 * 1	   | mono 12 bit packed
	 *
	 * \param iDepth accepts any of above values
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_set_pixel_depth(int iDepth);

	/**
	 * Reads pixel depth from camera.
	 * For values see PSL_VHR_set_pixel_depth().
	 *
	 * \return integer corresponding to any of above values
	 */
	LINKDLL int PSL_VHR_get_pixel_depth(void);

	/**
	 * Enables Test Chart image output of camera.
	 *
	 * \param bEnabled true or false
	 */
	LINKDLL void PSL_VHR_enable_test_chart(int bEnabled);

	/**
	 * Reads PLDboard FW creation date from camera.
	 *
	 * \param day (out) day component of date
	 * \param month (out) month component of date
	 * \param year (out) year component of date
	 */
	LINKDLL	void PSL_VHR_get_PLD_date(unsigned short *day, unsigned short *month, unsigned short *year);

	/**
	 * Get "DELAY_BETWEEN_IMAGES" parameters value from camera.
	 *
	 * \return DELAY_BETWEEN_IMAGES value
	 */
	LINKDLL	int PSL_VHR_get_delay_between_images(void);

	/**
	 * Set "DELAY_BETWEEN_IMAGES" param value in camera.
	 *
	 * \param delay value
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL	bool PSL_VHR_set_delay_between_images(int delay);

	///////////////////////////// INTERNALS

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Legacy function for SW combined gainmode8 images.\n
	 * Takes a 24 bit RGB packed image \n
	 * bottom 11 bits >> top of 16 bit image \n
	 * top 11 bits >> bottom of 16 bit image \n
	 *
	 * \param orig_image (in) pointer to memory location of image (24bit RGBpacked format)
	 * \param image_width (in) original image width, (out) after demangling image_width will be updated
	 * \param image_height (in) original image height (out) after demangling image_height will be updated
	 * \return pointer to demangled image memory location.
	 */
	LINKDLL	unsigned short *PSL_VHR_demangle_rgb24_into_16bit_image(unsigned char *orig_image, int *image_width, int *image_height);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Scales image data from 16bit to 8bit with use of a LUT.
	 * \note Original image 16bit data is overwritten with 8bit image data.
	 *
	 * \param orig_image pointer to start of original image memory location
	 * \param width orig_image width.
	 * \param height orig_image height.
	 * \param min Minimum pixel value to scale to.
	 * \param max Maximum pixel value to scale to.
	 */
	LINKDLL void PSL_VHR_scale_16_to_8(unsigned short *orig_image, int width, int height, int min, int max);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Enables WhiteBalance filter of the eBUS driver ONCE (GEV ONLY).
	 */
	LINKDLL void PSL_VHR_perform_once_only_white_balance(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Enables RGB Balance filter of the eBUS driver (GEV ONLY).
	 *
	 * \param bEnabled true or false
	 */
	LINKDLL void PSL_VHR_enable_white_balancing(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Applies filter reset of the eBUS driver (GEV ONLY).
	 */
	LINKDLL void PSL_VHR_reset_white_balance_gains(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * AVOID USE - Reloads camera calibration preset values from calibration file.\n
	 * \warning CAN OVERWRITE ALREADY INITIALIZED (by PSL_VHR_Open()) VALUES IN THE DRIVER!! \n
	 * DON'T USE UNLESS INSTRUCTED TO!!
	 *
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_load_camera_configuration_file(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - Write offset value ("BlackLevelRaw") to camera.
	 *
	 * \param offset value in range 0 to 1024
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_set_offset(int offset);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - Read offset value from camera "BlackLevelRaw".\n
	 *
	 * \return BlackLevelRaw value.
	 */
	LINKDLL int	PSL_VHR_get_offset();

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - Enables undefined bit of camera.
	 * NOT IMPLEMENTED ATM DEFFINITION ONLY HERE FOR BACKWARDS COMP.
	 *
	 * \param bEnabled true or false
	 */
	LINKDLL void PSL_VHR_enable_undefined_bit(int bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * Gets Calculated maxFF value.
	 *
	 * \return Calculated maxFF value
	 */
	LINKDLL unsigned long PSL_VHR_get_calculated_raw_maxff(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * Sets Calculated maxFF value.
	 *
	 * \param maxff Calculated maxFF value
	 */
	LINKDLL void PSL_VHR_set_raw_maxff(unsigned long maxff);

	/**
	 * INTERNAL USE ONLY.\n
	 * Allocates memory for no_images * buffer for sequence acquisition.
	 * 
	 * \param no_images number of images to allocate for
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_initialise_sequence_storage(unsigned long no_images);

	/**
	 * INTERNAL USE ONLY.\n
	 * Carries out a sequence acquisition of no_images_to_snap.
	 * Requires storage to be allocated by PSL_VHR_initialise_sequence_storage().
	 *
	 * \param no_images_to_snap number of images in sequence
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_snap_sequence(unsigned long no_images_to_snap);

	/**
	 * INTERNAL USE ONLY.\n
	 * Returns the address of the N-th image in the sequence, indexed from 1.
	 *
	 * \param pSequenceImage address of pointer
	 * \param image_required N-th image in the sequence buffer
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_get_sequence_image_pointer(unsigned short **pSequenceImage, unsigned long image_required);

	/**
	 * INTERNAL USE ONLY.\n
	 * Frees up allocated memory of sequence buffer.
	 *
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL bool PSL_VHR_free_sequence_storage(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * Saves images stored in sequence buffer starting with first as .flf file.
	 *
	 * \param no_images_to_save number of images to save
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL	bool PSL_VHR_save_sequence_as_multiple_flf_files(unsigned long no_images_to_save);

	/**
	 * INTERNAL USE ONLY.\n
	 * Save image at as flf into camera files directory.
	 *
	 * \param pImage pointer to memory location of image
	 * \param width image width
	 * \param height image height
	 * \param fname file name it should be saved as (including extension)
	 * \return true = success \n
	 *         false = failure \n
	 */
	LINKDLL	bool PSL_VHR_save_flf_image(unsigned short *pImage, int width, int height, char *fname);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - Enables image stamping in camera.
	 *
	 * \param bEnabled true or false
	 */
	LINKDLL	void PSL_VHR_enable_image_stamp(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Transfers data from pBuffer memory location to drivers safebufferC.
	 *
	 * \param pBuffer pointer to image memory location
	 */
	LINKDLL void PSL_VHR_transfer_to_safebufferC(unsigned short *pBuffer);

	/**
	 * INTERNAL USE ONLY.\n
	 * NOT USED ATM - Returns pointer to safebufferC memory location.
	 *
	 * \return pointer to safebufferC memory location
	 */
	LINKDLL unsigned short *PSL_VHR_get_pointer_to_safebufferC(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_combining_relative_gain(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_combining_relative_gain(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_combining_low_gain_offset(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_combining_low_gain_offset(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_combining_high_gain_offset(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_combining_high_gain_offset(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_gamma_gain_dark(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_gamma_gain_dark(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_chip_gain(unsigned long iChipGain);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_video_gain(unsigned long iVidGain);

	/**
	 * INTERNAL USE ONLY.\n
	 * Software bin 8bit image.
	 * \param orig_image original image buffer
	 * \param image_width pointer to variable where width of image is updated
	 * \param image_height pointer to variable where height of image is updated
	 * \param xbinning amount to bin the image by on x axis
	 * \param ybinning amount to bin the image by on y axis
	 */
	LINKDLL void PSL_VHR_software_bin_8bit_image(unsigned char *orig_image, int *image_width, int *image_height, int xbinning, int ybinning);

	/**
	 * INTERNAL USE ONLY.\n
	 * Legacy - To remap a double size (combined) image produced by 2-tap SCMOS.
	 */
	LINKDLL unsigned short *PSL_VHR_remap_double_image(unsigned short *orig_image, int *image_width, int *image_height, bool bSmoothingEnabled, bool bClippingEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_set_flicker_mode(int flicker_mode);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - 0 = off 1 = 50HZ 2 = 100MHZ
	 */
	LINKDLL int PSL_VHR_get_flicker_mode(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_ALC(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_ALC_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_ALC_max_exp(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - IN MICROSECS 1000 TO 65535
	 */
	LINKDLL bool PSL_VHR_set_ALC_max_exp(int maxexp);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_get_ALC_window_coords(int *xstart, int *ystart, int *xend, int *yend);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - x coordinates in range 0 to 1919 and y coordinates in range 0 to 1079
	 */
	LINKDLL bool PSL_VHR_set_ALC_window_coords(int xstart, int ystart, int xend, int yend);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_ALC_window_display(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_ALC_window_display_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - this depends on current ALC window dimensions
	 */
	LINKDLL int PSL_VHR_get_upper_limit_for_best_fit_up_threshold(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_set_best_fit_up_threshold(int threshval);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - a value between 1 and the maximum as returned by PSL_VHR_get_upper_limit_for_best_fit_up_threshold()
	 */
	LINKDLL int PSL_VHR_get_best_fit_up_threshold(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_bestfit(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_bestfit_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - EXPOSURE CONTROL: PEAK/AVERAGE\n
	 * 6 to whatever PSL_VHR_get_upper_limit_for_best_fit_up_threshold() returns\n
	 * (which depends on the dimensions of the control window)
	 */
	LINKDLL bool PSL_VHR_set_bestfit_peek(int bfpeek);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL int  PSL_VHR_get_bestfit_peek(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_bestfit_brightness(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_set_bestfit_brightness(int brightness);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL int PSL_VHR_get_gamma_gain_bright(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_gamma_gain_bright(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	int PSL_VHR_get_gamma_gain_brightness(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL	bool PSL_VHR_set_gamma_gain_brightness(int val);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_binning_filter(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_binning_filter_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_auto_binning_filter(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_auto_binning_filter_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL void PSL_VHR_enable_gamma(bool bEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 */
	LINKDLL bool PSL_VHR_gamma_is_enabled(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 * \note CamLink ONLY!
	 */
	LINKDLL bool PSL_VHR_NION_acquire_sequence(unsigned long seqlength, unsigned short *pMem);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.
	 * \note CamLink ONLY!
	 */
	LINKDLL bool PSL_VHR_NION_is_sequence_acquisition_active(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - Cyclops type high precision remapping.
	 * 
	 * \note To use the high precision functions, a map file should already have\n
	 * been loaded via a call to PSL_VHR_open_map(char *mapfile) (see above)\n
	 * tune the mapping parameters
	 */
	LINKDLL	void PSL_VHR_configure_high_precision_mapping(unsigned short xorigin, unsigned short yorigin, int rotation, unsigned short subwidth, unsigned short subheight, bool bAngularEnabled);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - This should be called initially AND whenever map origin, rotation, subarea,\n
	 * angular, or binning have changed in order to re-generate the working map.
	 */
	LINKDLL	bool PSL_VHR_generate_high_precision_working_map(void);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - Call this after calling PSL_VHR_generate_high_precision_working_map() to find the\n
	 * new dimensions of the remapped image (lets us find these dimensions before we actually\n
	 * perform the mapping using PSL_VHR_perform_high_precision_remap() below)
	 */
	LINKDLL	void PSL_VHR_get_high_precision_remapped_image_dimensions(int *working_mapwidth, int *working_mapheight);

	/**
	 * INTERNAL USE ONLY.\n
	 * N/A ATM - ONLY HERE FOR BACKWARDS COMP.\n
	 * Legacy - remap an image
	 */
	LINKDLL	unsigned short *PSL_VHR_perform_high_precision_remap(unsigned short *orig_image, bool bSmoothingEnabled);
#ifdef __cplusplus
};
#endif



#endif /* _PSL_VHR_H_ */
