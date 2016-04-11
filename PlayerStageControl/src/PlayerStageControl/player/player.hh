/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autor: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
 *
 * This file is part of PlayerStageControl project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef PLAYER_HH
#define PLAYER_HH

#include <libplayerc/playerc.h>
#include <PlayerStageControl/player/baseplayer.hh>
#include <PlayerStageControl/player/sensor/basesensors.hh>
#include <PlayerStageControl/utils/thread/thread.hh>

class Player : public Thread {
public:
    Player(const char *host = "localhost", int port = 6665);
    ~Player();

    // Connection and execution
    bool connect();
    bool disconnect();

    // Player position and orientation
    Position position() const;
    float orientation() const;

    // Position/orientation auxiliary
    bool isAtPosition(const Position &pos);
    bool isLookingTo(const Position &pos);

    // Behavior
    void setBehavior(Behavior *behavior);

    // Locomotion layer 1
    void goTo(const Position &destination, bool avoidObstacles);
    void goToLookTo(const Position &destination, const Position &posToLook, bool avoidObstacles);
    void lookTo(const Position &position, bool avoidObstacles);
    void idle();

    // Locomotion layer 0
    void setSpeed(float x, float y, float theta);

    // Debug
    void printError();
private:
    // Thread implementation
    void initialization();
    void loop();
    void finalization();

    // Playerc connection
    playerc_client_t *_client;

    // Behavior
    Behavior *_behavior;

    // Navigation
    Navigation *_nav;

    // Sensors
    Odometer *_odometer;
    Laser *_laser;

    // Errors
    float _lError;
    float _aError;

    // Max speeds
    float _maxLSpeed;
    float _maxASpeed;

    // Speed calc
    float getLinearSpeed(float distError);
    float getAngularSpeed(float angError);

    // Sensors
    void connectSensors();
    void disconnectSensors();

    // Internal
    void update();
};

#endif // PLAYER_HH