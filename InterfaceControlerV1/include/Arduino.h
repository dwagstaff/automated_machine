/*
 * Arduino.h
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <stdint.h>

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
	#define assert_true(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  extern "C" void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_true(expr) ((void)0)
#endif /* USE_FULL_ASSERT */



class Arduino {
private:
public:
	/**
	 * Delay for xx milliseconds
	 * @param ms - Milliseconds to delay for
	 */
	static void delay(uint16_t ms);
};




#endif /* ARDUINO_H_ */
