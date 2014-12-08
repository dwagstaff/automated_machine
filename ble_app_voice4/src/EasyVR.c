/*
 EasyVR library v1.5
 Copyright (C) 2014 RoboTech srl

 Written for Arduino and compatible boards for use with EasyVR modules or
 EasyVR Shield boards produced by VeeaR <www.veear.eu>

 Released under the terms of the MIT license, as found in the accompanying
 file COPYING.txt or at this address: <http://www.opensource.org/licenses/MIT>
 */

#include "protocol.h"
#include <ctype.h>

#include "simple_uart.h"
#include "nrf_delay.h"
#include "EasyVR.h"

/*****************************************************************************/

void EasyVR_sendCmd(uint8_t c) {
	nrf_delay_ms(10);
	simple_uart_put(c);
}

void EasyVR_send(uint8_t c) {
//  delay(1);
	nrf_delay_ms(1);
//  _s->write(c);
	simple_uart_put(c);
}

void EasyVR_sendArg(int8_t c) {
	if( c == 0xff )
		EasyVR_send('@');
	else
		EasyVR_send(c + ARG_ZERO);
}

bool EasyVR_isConflict() {
	return _status.b._conflict;
}
bool EasyVR_isMemoryFull() {
	return _status.b._memfull;
}
int8_t EasyVR_getCommand() {
	return _status.b._command ? _value : -1;
}
int8_t EasyVR_getWord() {
	return _status.b._builtin ? _value : -1;
}
int16_t EasyVR_getToken() {
	return _status.b._token ? _value : -1;
}
int16_t EasyVR_getError() {
	return _status.b._error ? _value : -1;
}
bool EasyVR_isTimeout() {
	return _status.b._timeout;
}
bool EasyVR_isAwakened() {
	return _status.b._awakened;
}

void EasyVR_sendGroup(int8_t c) {
//  delay(1);
	nrf_delay_ms(1);
//  _s->write(c + ARG_ZERO);
	simple_uart_put(c + ARG_ZERO);
//  delay(19); // worst case time to cache a full group in memory
	nrf_delay_ms(19);
}

int EasyVR_recv(int16_t timeout) // negative means forever
{
//  while (timeout != 0 && _s->available() == 0)
//  {
//    delay(1);
//    if (timeout > 0)
//      --timeout;
//  }
//  return _s->read();
	//TODO - Need to implement timeout featue
	return simple_uart_get();
}

bool EasyVR_recvArg(int8_t* c, int16_t timeout) {
	EasyVR_send(ARG_ACK);
	int r = EasyVR_recv(timeout);
	*c = r - ARG_ZERO;
	return r >= ARG_MIN && r <= ARG_MAX;
}

/*****************************************************************************/

bool EasyVR_detect() {
	uint8_t i;
	for (i = 0; i < 5; ++i) {
		EasyVR_sendCmd(CMD_BREAK);

		if (EasyVR_recv(WAKE_TIMEOUT) == STS_SUCCESS)
			return true;
	}
	return false;
}

bool EasyVR_stop() {
	EasyVR_sendCmd(CMD_BREAK);

	uint8_t rx = EasyVR_recv(WAKE_TIMEOUT);
	if (rx == STS_INTERR || rx == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_sleep(int8_t mode) {
	EasyVR_sendCmd(CMD_SLEEP);
	EasyVR_sendArg(mode);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

int8_t EasyVR_getID() {
	EasyVR_sendCmd(CMD_ID);
	if (EasyVR_recv(DEF_TIMEOUT) == STS_ID) {
		int8_t rx;
		if (EasyVR_recvArg(&rx, DEF_TIMEOUT))
			return rx;
	}
	return -1;
}

bool EasyVR_setLanguage(int8_t lang) {
	EasyVR_sendCmd(CMD_LANGUAGE);
	EasyVR_sendArg(lang);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setTimeout(int8_t seconds) {
	EasyVR_sendCmd(CMD_TIMEOUT);
	EasyVR_sendArg(seconds);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setMicDistance(int8_t dist) {
	EasyVR_sendCmd(CMD_MIC_DIST);
	EasyVR_sendArg(-1);
	EasyVR_sendArg(dist);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setKnob(int8_t knob) {
	EasyVR_sendCmd(CMD_KNOB);
	EasyVR_sendArg(knob);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setLevel(int8_t level) {
	EasyVR_sendCmd(CMD_LEVEL);
	EasyVR_sendArg(level);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setDelay(uint16_t millis) {
	EasyVR_sendCmd(CMD_DELAY);
	if (millis <= 10)
		EasyVR_sendArg(millis);
	else if (millis <= 100)
		EasyVR_sendArg(millis / 10 + 9);
	else if (millis <= 1000)
		EasyVR_sendArg(millis / 100 + 18);
	else
		return false;

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_changeBaudrate(int8_t baud) {
	EasyVR_sendCmd(CMD_BAUDRATE);
	EasyVR_sendArg(baud);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_addCommand(int8_t group, int8_t index) {
	EasyVR_sendCmd(CMD_GROUP_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);

	int rx = EasyVR_recv(DEF_TIMEOUT);
	if (rx == STS_SUCCESS)
		return true;
	_status.v = 0;
	if (rx == STS_OUT_OF_MEM)
		_status.b._memfull = true;
	return false;
}

bool EasyVR_removeCommand(int8_t group, int8_t index) {
	EasyVR_sendCmd(CMD_UNGROUP_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_setCommandLabel(int8_t group, int8_t index, const char* name) {
	EasyVR_sendCmd(CMD_NAME_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);

	int8_t len = 31;
	for (const char* p = name; *p != 0 && len > 0; ++p, --len) {
		if (isdigit(*p))
			--len;
	}
	len = 31 - len;

	EasyVR_sendArg(len);
	for (int8_t i = 0; i < len; ++i) {
		char c = name[i];
		if (isdigit(c)) {
			EasyVR_send('^');
			EasyVR_sendArg(c - '0');
		} else if (isalpha(c)) {
			EasyVR_send(c & ~0x20); // to uppercase
		} else {
			EasyVR_send('_');
		}
	}

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_eraseCommand(int8_t group, int8_t index) {
	EasyVR_sendCmd(CMD_ERASE_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_getGroupMask(uint32_t* mask) {
	EasyVR_sendCmd(CMD_MASK_SD);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_MASK) {
		int8_t rx;
		mask = 0;
		for (int8_t i = 0; i < 4; ++i) {
			if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
				return false;
			((uint8_t*) &mask)[i] |= rx & 0x0F;
			if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
				return false;
			((uint8_t*) &mask)[i] |= (rx << 4) & 0xF0;
		}
		return true;
	}
	return false;
}

int8_t EasyVR_getCommandCount(int8_t group) {
	EasyVR_sendCmd(CMD_COUNT_SD);
	EasyVR_sendArg(group);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_COUNT) {
		int8_t rx;
		if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
			return rx == -1 ? 32 : rx;
		}
	}
	return -1;
}

bool EasyVR_dumpCommand(int8_t group, int8_t index, char* name,
		uint8_t* training) {
	EasyVR_sendCmd(CMD_DUMP_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);

	if (EasyVR_recv(DEF_TIMEOUT) != STS_DATA)
		return false;

	int8_t rx;
	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	*training = rx & 0x07;
	if (rx == -1 || *training == 7)
		training = 0;

	_status.v = 0;
	_status.b._conflict = (rx & 0x18) != 0;
	_status.b._command = (rx & 0x08) != 0;
	_status.b._builtin = (rx & 0x10) != 0;

	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	_value = rx;

	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	int8_t len = rx == -1 ? 32 : rx;
	for (; len > 0; --len, ++name) {
		if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
			return false;
		if (rx == '^' - ARG_ZERO) {
			if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
				return false;
			*name = '0' + rx;
			--len;
		} else {
			*name = ARG_ZERO + rx;
		}
	}
	*name = 0;
	return true;
}

int8_t EasyVR_getGrammarsCount(void) {
	EasyVR_sendCmd(CMD_DUMP_SI);
	EasyVR_sendArg(-1);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_COUNT) {
		int8_t rx;
		if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
			return rx == -1 ? 32 : rx;
		}
	}
	return -1;
}

bool EasyVR_dumpGrammar(int8_t grammar, uint8_t* flags, uint8_t* count) {
	EasyVR_sendCmd(CMD_DUMP_SI);
	EasyVR_sendArg(grammar);

	if (EasyVR_recv(DEF_TIMEOUT) != STS_GRAMMAR)
		return false;

	int8_t rx;
	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	*flags = rx == -1 ? 32 : rx;

	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	*count = rx;
	return true;
}

bool EasyVR_getNextWordLabel(char* name) {
	int8_t count;
	if (!EasyVR_recvArg(&count, DEF_TIMEOUT))
		return false;
	if (count == -1)
		count = 32;

	for (; count > 0; --count, ++name) {
		int8_t rx;
		if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
			return false;

		if (rx == '^' - ARG_ZERO) {
			if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
				return false;

			*name = '0' + rx;
			--count;
		} else {
			*name = ARG_ZERO + rx;
		}
	}
	*name = 0;
	return true;
}

void EasyVR_trainCommand(int8_t group, int8_t index) {
	EasyVR_sendCmd(CMD_TRAIN_SD);
	EasyVR_sendGroup(group);
	EasyVR_sendArg(index);
}

void EasyVR_recognizeCommand(int8_t group) {
	EasyVR_sendCmd(CMD_RECOG_SD);
	EasyVR_sendArg(group);
}

void EasyVR_recognizeWord(int8_t wordset) {
	EasyVR_sendCmd(CMD_RECOG_SI);
	EasyVR_sendArg(wordset);
}

bool EasyVR_hasFinished() {
	int8_t rx = EasyVR_recv(NO_TIMEOUT);
	if (rx < 0)
		return false;

	_status.v = 0;
	_value = 0;

	switch (rx) {
	case STS_SUCCESS:
		return true;

	case STS_SIMILAR:
		_status.b._builtin = true;
		goto GET_WORD_INDEX;

	case STS_RESULT:
		_status.b._command = true;

		GET_WORD_INDEX: if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
			_value = rx;
			return true;
		}
		break;

	case STS_TOKEN:
		_status.b._token = true;

		if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
			_value = rx << 5;
			if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
				_value |= rx;
				return true;
			}
		}
		break;

	case STS_AWAKEN:
		_status.b._awakened = true;
		return true;

	case STS_TIMEOUT:
		_status.b._timeout = true;
		return true;

	case STS_INVALID:
		_status.b._invalid = true;
		return true;

	case STS_ERROR:
		_status.b._error = true;
		if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
			_value = rx << 4;
			if (EasyVR_recvArg(&rx, DEF_TIMEOUT)) {
				_value |= rx;
				return true;
			}
		}
		break;
	}

	// unexpected condition (communication error)
	_status.v = 0;
	_status.b._error = true;
	_value = 0;
	return true;
}

bool EasyVR_setPinOutput(int8_t pin, int8_t value) {
	EasyVR_sendCmd(CMD_QUERY_IO);
	EasyVR_sendArg(pin);
	EasyVR_sendArg(value);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

int8_t EasyVR_getPinInput(int8_t pin, int8_t config) {
	EasyVR_sendCmd(CMD_QUERY_IO);
	EasyVR_sendArg(pin);
	EasyVR_sendArg(config);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_PIN) {
		int8_t rx;
		if (EasyVR_recvArg(&rx, DEF_TIMEOUT))
			return rx;
	}
	return -1;
}

bool EasyVR_playPhoneTone(int8_t tone, uint8_t duration) {
	EasyVR_sendCmd(CMD_PLAY_DTMF);
	EasyVR_sendArg(-1); // distinguish DTMF from SX
	EasyVR_sendArg(tone);
	EasyVR_sendArg(duration - 1);

	if (EasyVR_recv(
			(tone < 0 ? duration * 1000 : duration * 40)
					+ DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_playSound(int16_t index, int8_t volume) {
	EasyVR_sendCmd(CMD_PLAY_SX);
	EasyVR_sendArg((index >> 5) & 0x1F);
	EasyVR_sendArg(index & 0x1F);
	EasyVR_sendArg(volume);

	if (EasyVR_recv(PLAY_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

void EasyVR_playSoundAsync(int16_t index, int8_t volume) {
	EasyVR_sendCmd(CMD_PLAY_SX);
	EasyVR_sendArg((index >> 5) & 0x1F);
	EasyVR_sendArg(index & 0x1F);
	EasyVR_sendArg(volume);
}

void EasyVR_detectToken(int8_t bits, int8_t rejection, uint16_t timeout) {
	EasyVR_sendCmd(CMD_RECV_SN);
	EasyVR_sendArg(bits);
	EasyVR_sendArg(rejection);
	if (timeout > 0)
		timeout = (timeout * 2 + 53) / 55; // approx / 27.46 - err < 0.15%
	EasyVR_sendArg((timeout >> 5) & 0x1F);
	EasyVR_sendArg(timeout & 0x1F);
}

bool EasyVR_sendToken(int8_t bits, uint8_t token) {
	EasyVR_sendCmd(CMD_SEND_SN);
	EasyVR_sendArg(bits);
	EasyVR_sendArg((token >> 5) & 0x1F);
	EasyVR_sendArg(token & 0x1F);
	EasyVR_sendArg(0);
	EasyVR_sendArg(0);

	if (EasyVR_recv(TOKEN_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

void EasyVR_sendTokenAsync(int8_t bits, uint8_t token) {
	EasyVR_sendCmd(CMD_SEND_SN);
	EasyVR_sendArg(bits);
	EasyVR_sendArg((token >> 5) & 0x1F);
	EasyVR_sendArg(token & 0x1F);
	EasyVR_sendArg(0);
	EasyVR_sendArg(0);
}

bool EasyVR_embedToken(int8_t bits, uint8_t token, uint16_t delay) {
	EasyVR_sendCmd(CMD_SEND_SN);
	EasyVR_sendArg(bits);
	EasyVR_sendArg((token >> 5) & 0x1F);
	EasyVR_sendArg(token & 0x1F);
	delay = (delay * 2 + 27) / 55; // approx / 27.46 - err < 0.15%
	if (delay == 0) // must be > 0 to embed in some audio
		delay = 1;
	EasyVR_sendArg((delay >> 5) & 0x1F);
	EasyVR_sendArg(delay & 0x1F);

	if (EasyVR_recv(DEF_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

bool EasyVR_dumpSoundTable(char* name, int16_t* count) {
	EasyVR_sendCmd(CMD_DUMP_SX);

	if (EasyVR_recv(DEF_TIMEOUT) != STS_TABLE_SX)
		return false;

	int8_t rx;
	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	*count = rx << 5;
	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	*count |= rx;

	if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
		return false;
	int len = rx;
	for (int8_t i = 0, k = 0; i < len; ++i, ++k) {
		if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
			return false;
		if (rx == '^' - ARG_ZERO) {
			if (!EasyVR_recvArg(&rx, DEF_TIMEOUT))
				return false;
			++i;
			name[k] = '0' + rx;
		} else {
			name[k] = ARG_ZERO + rx;
		}
	}
	name[len] = 0;
	return true;
}

bool EasyVR_resetAll() {
	EasyVR_sendCmd(CMD_RESETALL);
	EasyVR_sendArg(17);

	if (EasyVR_recv(RESET_TIMEOUT) == STS_SUCCESS)
		return true;
	return false;
}

/** @mainpage

 <table><tr><td>
 <img src="EasyVR_2.jpg" alt="EasyVR module" title="EasyVR module">
 </td><td>
 <img src="EasyVR_Shield_2.jpg" alt="EasyVR Shield" title="EasyVR Shield">
 </td></tr></table>

 The %EasyVR library implements the serial communication protocol to
 manage the %EasyVR module and the EasyVR Shield from Arduino boards and
 controllers and it enables easy access to all the EasyVR features.

 The library is composed of two classes:
 - #EasyVR
 - #EasyVRBridge

 Examples for using the library are available from inside the Arduino
 IDE, as for any other library (menu File > Examples > %EasyVR).
 */
