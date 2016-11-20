#include <FlightController.hpp>
#include <msp_msg.hpp>
#include <msp_msg.hpp>

#include <iostream>

#include <msg_print.hpp>

class App {
public:
    std::string name;

    App(std::string name) {
        this->name = name;
    }

    void onIdent(const msp::Ident* const ident) {
        std::cout<<"Name: "<<name<<std::endl;
        std::cout<<(*ident);
    }

    void onStatus(const msp::Status *status) {
        std::cout<<"Name: "<<name<<std::endl;
        std::cout<<(*status);
    }

    void onImu(const msp::Imu* const imu) {
        std::cout<<"Name: "<<name<<std::endl;
        std::cout<<(*imu);
    }

    void onServo(const msp::Servo* const servo) {
        std::cout<<(*servo);
    }

    void onMotor(const msp::Motor* const motor) {
        std::cout<<(*motor);
    }

    void onRc(const msp::Rc* const rc) {
        std::cout<<(*rc);
    }

    void onAttitude(const msp::Attitude* const attitude) {
        std::cout<<(*attitude);
    }

    void onAltitude(const msp::Altitude* const altitude) {
        std::cout<<(*altitude);
    }

    void onAnalog(const msp::Analog* const analog) {
        std::cout<<(*analog);
    }

    void onRcTuning(const msp::RcTuning* const rc_tuning) {
        std::cout<<(*rc_tuning);
    }

    void onPID(const msp::Pid* const pid) {
        std::cout<<(*pid);
    }

    void onBox(const msp::Box* const box) {
        std::cout<<(*box);
    }

    void onMisc(const msp::Misc* const misc) {
        std::cout<<(*misc);
    }

    void onMotorPins(const msp::MotorPins* const motor_pins) {
        std::cout<<(*motor_pins);
    }

    void onBoxNames(const msp::BoxNames* const box_names) {
        std::cout<<(*box_names);
    }

    void onPidNames(const msp::PidNames* const pid_names) {
        std::cout<<(*pid_names);
    }

    void onBoxIds(const msp::BoxIds* const box_ids) {
        std::cout<<(*box_ids);
    }

    void onServoConf(const msp::ServoConf* const servo_conf) {
        std::cout<<(*servo_conf);
    }

    void onDebugMessage(const msp::DebugMessage* const debug_msg) {
        std::cout<<"#Debug message:"<<std::endl;
        std::cout<<(*debug_msg).msg<<std::endl;
    }

    void onDebug(const msp::Debug* const debug) {
        std::cout<<(*debug);
    }
};

int main(int argc, char *argv[]) {
    std::string device;
    if(argc>1)
        device = std::string(argv[1]);
    else
        device = "/dev/ttyUSB0";

    fcu::FlightController fcu(device);
    fcu.setAcc1G(512.0);
    fcu.setGyroUnit(1.0/4096);
    fcu.setMagnGain(1090.0/100.0);
    fcu.setStandardGravity(9.80665);
    fcu.populate_all();

    sleep(8);
    std::cout<<"MSP ready"<<std::endl;


    App app("MultiWii");
    fcu.subscribe(msp::ID::MSP_IDENT, &App::onIdent, &app);
    fcu.subscribe(msp::ID::MSP_STATUS, &App::onStatus, &app);
    fcu.subscribe(msp::ID::MSP_RAW_IMU, &App::onImu, &app);
    fcu.subscribe(msp::ID::MSP_SERVO, &App::onServo, &app);
    fcu.subscribe(msp::ID::MSP_MOTOR, &App::onMotor, &app);
    fcu.subscribe(msp::ID::MSP_RC, &App::onRc, &app);
    // TODO: RawGPS
    // TODO: CompGPS
    fcu.subscribe(msp::ID::MSP_ATTITUDE, &App::onAttitude, &app);
    fcu.subscribe(msp::ID::MSP_ALTITUDE, &App::onAltitude, &app);
    fcu.subscribe(msp::ID::MSP_ANALOG, &App::onAnalog, &app);
    fcu.subscribe(msp::ID::MSP_RC_TUNING, &App::onRcTuning, &app);
    fcu.subscribe(msp::ID::MSP_PID, &App::onPID, &app);
    fcu.subscribe(msp::ID::MSP_BOX, &App::onBox, &app);
    fcu.subscribe(msp::ID::MSP_MISC, &App::onMisc, &app);
    fcu.subscribe(msp::ID::MSP_MOTOR_PINS, &App::onMotorPins, &app);
    fcu.subscribe(msp::ID::MSP_BOXNAMES, &App::onBoxNames, &app);
    fcu.subscribe(msp::ID::MSP_PIDNAMES, &App::onPidNames, &app);
    // TODO: WayPoint
    fcu.subscribe(msp::ID::MSP_BOXIDS, &App::onBoxIds, &app);
    fcu.subscribe(msp::ID::MSP_SERVO_CONF, &App::onServoConf, &app);
    // TODO: NavStatus
    // TODO: NavConfig
    fcu.subscribe(msp::ID::MSP_DEBUGMSG, &App::onDebugMessage, &app);
    fcu.subscribe(msp::ID::MSP_DEBUG, &App::onDebug, &app);

    while(true) {
        fcu.handle();
    }
}
