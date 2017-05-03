#include <systemc.h>

#ifndef TURNOFEVENTS_H
#define TURNOFEVENTS_H

SC_MODULE(TurnOfEvents)
{
    enum Directions {
        STOP = 's',
        QUIT = 'q',
        OFF = 'f',
        LEFT = 'l',
        RIGHT = 'r'

    };

    SC_CTOR(TurnOfEvents)
    {
        SC_THREAD(turn_knob_thread);

        SC_THREAD(left_signal_thread);

        SC_THREAD(right_signal_thread);

        SC_THREAD(stop_signal_thread);
    }

    sc_event signal_right, signal_left, signal_stop, signals_off;
    sc_event right_blinking, right_off;
    sc_event left_blinking, left_off;
    sc_event stop_blinking, stop_off;

    void turn_knob_thread();

    void left_signal_thread();

    void right_signal_thread();

    void stop_signal_thread();
};

void TurnOfEvents::turn_knob_thread()
{
    bool left_on, right_on, stop_on;

    char direction;

    wait(SC_ZERO_TIME);

    std::cout   << "Commands are (case sensitive):" << std::endl
                << " l => Left turn signal on" << std::endl
                << " r => Right turn signal on" << std::endl
                << " s => Stop signal on" << std::endl
                << " f => turn all signals oFF" << std::endl
                << " q => Quit program" << std::endl
                << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    while(true) {
        std::cout << "Signal command [l/r/s/f/q]: " << std::endl;
        std::cin >> direction;

        switch (direction) {
            case OFF:
                signals_off.notify();
                if (right_on && left_on && stop_on) {
                    wait(right_off & left_off & stop_off);
                } else if (right_on && left_on) {
                    wait(right_off & left_off);
                } else if (right_on && stop_on) {
                    wait(right_off & stop_off);
                } else if (left_on && stop_on) {
                    wait(left_off & stop_off);
                } else if (right_on) {
                    wait(right_off);
                } else if (left_on) {
                    wait(left_off);
                } else if (stop_on) {
                    wait(stop_off);
                    right_on = left_on = stop_on = false;
                }
                continue;
            case QUIT:
                std::cout << "Quiting" << std::endl;
                sc_stop();
                return;
                continue;
            case STOP:
                signal_stop.notify();
                if (!stop_on) {
                    wait(stop_blinking);
                } else {
                    std::cout << "INFO: Stop signal is aready on." << std::endl;
                    stop_on = true;
                }
                continue;
            case LEFT:
                signal_left.notify();
                if (!left_on) {
                    wait(left_blinking);
                } else {
                    std::cout << "INFO: Left signal is aready on." << std::endl;
                    left_on = true;
                }
                continue;
            case RIGHT:
                signal_right.notify();
                if (!right_on) {
                    wait(right_blinking);
                } else {
                    std::cout << "INFO: Right signal is already on." << std::endl;
                    right_on = true;
                }
                continue;
            default:
                continue;
        }
    }
}

void TurnOfEvents::left_signal_thread()
{
    while (true) {
        wait(signal_left);
        std::cout << "Turning left!!!"  << std::endl;
        left_blinking.notify();

        wait(signals_off);
        std::cout << "Left off" << std::endl;
        stop_off.notify();
    }
}

void TurnOfEvents::right_signal_thread()
{
    while (true) {
        wait(signal_right);
        std::cout << "Turning right!!!"  << std::endl;
        right_blinking.notify();

        wait(signals_off);
        std::cout << "Right off" << std::endl;
        stop_off.notify();
    }
}

void TurnOfEvents::stop_signal_thread()
{
    while (true) {
        wait(signal_stop);
        std::cout << "Stopping!!!" << std::endl;
        stop_blinking.notify();

        wait(signals_off);
        std::cout << "Stop off" << std::endl;
        stop_off.notify();
    }
}

#endif // TURNOFEVENTS_H
