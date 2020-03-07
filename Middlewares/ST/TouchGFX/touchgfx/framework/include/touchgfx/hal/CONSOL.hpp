/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef CONSOL_HPP
#define CONSOL_HPP

namespace touchgfx
{
/**
 * @class CONSOL CONSOL.hpp touchgfx/hal/CONSOL.hpp
 *
 * @brief Interface class for manipulating CONSOL in order to do performance measurements on target.
 *
 *        Interface class for manipulating CONSOL in order to do performance measurements on
 *        target. Not used on the PC simulator.
 */
class CONSOL
{
public:

    /**
     * @fn static void CONSOL::init();
     *
     * @brief Perform configuration of CONSOL pins.
     *
     *        Perform configuration of CONSOL pins.
     */
    static void init();

    /**
     * @fn static void CONSOL::set();
     *
     * @brief Sets a pin high.
     *
     *        Sets a pin high.
     *
     * @param id the pin to set.
     */
    static void transmit(char* data,int len);

}; // class GPIO
} // namespace touchgfx

#endif // CONSOL_HPP
