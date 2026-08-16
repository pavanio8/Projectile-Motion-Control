#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct State {
    double t;
    double x;
    double y;
    double vx;
    double vy;
};

class Projectile {
private:
    double g;
    double k;
    double m;
    double dt;
    State state;

    State step(const State& s) {
        double velocity = sqrt(s.vx * s.vx + s.vy * s.vy);

        // Acceleration due to air resistance
        double ax = -(k / m) * velocity * s.vx;
        double ay = -g - (k / m) * velocity * s.vy;

        // Update velocity
        double newVx = s.vx + ax * dt;
        double newVy = s.vy + ay * dt;

        // Update position
        double newX = s.x + newVx * dt;
        double newY = s.y + newVy * dt;

        State next;
        next.t = s.t + dt;
        next.x = newX;
        next.y = newY;
        next.vx = newVx;
        next.vy = newVy;

        return next;
    }

public:
    Projectile(double speed, double angleDeg, double gravity,
               double dragCoeff, double mass, double timeStep) {

        g = gravity;
        k = dragCoeff;
        m = mass;
        dt = timeStep;

        const double PI = 3.14159265358979323846;
        double angleRad = angleDeg * PI / 180.0;

        state.t = 0.0;
        state.x = 0.0;
        state.y = 0.0;
        state.vx = speed * cos(angleRad);
        state.vy = speed * sin(angleRad);
    }

    vector<State> simulate() {
        vector<State> history;

        history.push_back(state);

        while (true) {
            State next = step(state);

            history.push_back(next);

            // Stop when projectile reaches the ground
            if (next.y <= 0.0 && next.t > 0.0) {
                break;
            }

            state = next;

            // Safety limit
            if (state.t >= 10000.0) {
                break;
            }
        }

        return history;
    }
};

void printTrajectory(const vector<State>& history, int everyN) {

    cout << "\n";
    cout << "================ TRAJECTORY ================\n";

    cout << setw(8) << "t(s)"
         << setw(12) << "x(m)"
         << setw(12) << "y(m)"
         << setw(14) << "vx(m/s)"
         << setw(14) << "vy(m/s)"
         << "\n";

    cout << "--------------------------------------------------------------\n";

    cout << fixed << setprecision(2);

    for (size_t i = 0; i < history.size(); i += everyN) {

        const State& s = history[i];

        cout << setw(8) << s.t
             << setw(12) << s.x
             << setw(12) << s.y
             << setw(14) << s.vx
             << setw(14) << s.vy
             << "\n";
    }

    // Print final state if it was skipped
    if ((history.size() - 1) % everyN != 0) {

        const State& s = history.back();

        cout << setw(8) << s.t
             << setw(12) << s.x
             << setw(12) << s.y
             << setw(14) << s.vx
             << setw(14) << s.vy
             << "\n";
    }
}

void printSummary(const vector<State>& history) {

    double maxHeight = 0.0;
    double range = 0.0;
    double flightTime = 0.0;

    for (size_t i = 0; i < history.size(); i++) {

        if (history[i].y > maxHeight) {
            maxHeight = history[i].y;
        }

        range = history[i].x;
        flightTime = history[i].t;
    }

    cout << fixed << setprecision(3);

    cout << "\n";
    cout << "================ RESULTS ================\n";
    cout << "Maximum Height : " << maxHeight << " m\n";
    cout << "Time of Flight : " << flightTime << " s\n";
    cout << "Range          : " << range << " m\n";
    cout << "==========================================\n";
}

int main() {

    double speed;
    double angle;
    double gravity;
    double dt;
    double mass = 1.0;
    double dragCoeff = 0.0;

    char dragChoice;

    cout << "==========================================\n";
    cout << "       PROJECTILE MOTION SIMULATOR\n";
    cout << "==========================================\n";

    cout << "Enter initial speed (m/s): ";
    cin >> speed;

    cout << "Enter launch angle (degrees): ";
    cin >> angle;

    cout << "Enter gravity (m/s^2): ";
    cin >> gravity;

    cout << "Enter time step dt (seconds): ";
    cin >> dt;

    // Validate basic inputs
    if (speed <= 0) {
        cout << "Error: Speed must be greater than 0.\n";
        return 1;
    }

    if (angle <= 0 || angle >= 90) {
        cout << "Error: Angle must be between 0 and 90 degrees.\n";
        return 1;
    }

    if (gravity <= 0) {
        cout << "Error: Gravity must be greater than 0.\n";
        return 1;
    }

    if (dt <= 0) {
        cout << "Error: Time step must be greater than 0.\n";
        return 1;
    }

    cout << "Include air resistance? (y/n): ";
    cin >> dragChoice;

    if (dragChoice == 'y' || dragChoice == 'Y') {

        cout << "Enter mass (kg): ";
        cin >> mass;

        cout << "Enter drag coefficient k: ";
        cin >> dragCoeff;

        if (mass <= 0) {
            cout << "Error: Mass must be greater than 0.\n";
            return 1;
        }

        if (dragCoeff < 0) {
            cout << "Error: Drag coefficient cannot be negative.\n";
            return 1;
        }
    }
    else if (dragChoice == 'n' || dragChoice == 'N') {

        mass = 1.0;
        dragCoeff = 0.0;
    }
    else {

        cout << "Error: Please enter y or n.\n";
        return 1;
    }

    // Create projectile
    Projectile projectile(
        speed,
        angle,
        gravity,
        dragCoeff,
        mass,
        dt
    );

    // Run simulation
    vector<State> history = projectile.simulate();

    // Display approximately 20 rows
    int everyN = max(
        1,
        static_cast<int>(history.size() / 20)
    );

    printTrajectory(history, everyN);

    printSummary(history);

    return 0;
}
