#include "stm32f10x.h"
#include "motor.h"
#include "nf/nfv2.h"
#include "systick.h"

extern MOTOR_St				Motor;
extern NF_STRUCT_ComBuf 	NFComBuf;
extern STDOWNCNT_St		STDownCnt[ST_Downcounters];

void requestStatus(uint32_t *status, uint8_t *mode) {
	((uint16_t*)status)[0] = NFComBuf.ReadDrivesStatus.data[0];
	((uint16_t*)status)[1] = NFComBuf.ReadDigitalInputs.data[0];
	mode[0] = Motor.mode;
	ST_Reset(ST_CommandWD);
}

void requestPosition(int32_t *position) {
	*position = Motor.currentPosition;
	ST_Reset(ST_CommandWD);
}

void requestVelocity(int32_t *velocity) {
	*velocity = Motor.currentIncrement;
	ST_Reset(ST_CommandWD);
}

void setMode(uint8_t mode) {
	NFComBuf.SetDrivesMode.data[0] = mode;
	ST_Reset(ST_CommandWD);
}

void setPWM(int16_t pwm) {
	NFComBuf.SetDrivesPWM.data[0] = pwm;
	ST_Reset(ST_CommandWD);
}

void setTrq(int16_t trq) {
	NFComBuf.SetDrivesCurrent.data[0] = trq;
	ST_Reset(ST_CommandWD);
}

void setVel(int32_t vel) {
	NFComBuf.SetDrivesSpeed.data[0] = vel;
	ST_Reset(ST_CommandWD);
}

void setPos(int32_t pos) {
	NFComBuf.SetDrivesPosition.data[0] = pos;
	ST_Reset(ST_CommandWD);
}
