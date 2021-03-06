/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autores: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
 *          Luiz Felipe Machado Votto     (luizvotto@gmail.com)        - nUSP 8504006
 *          Nuno Bernardes Barcellos      (nunobarcellos@gmail.com)    - nUSP 8955132
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

#ifndef ODOMETER_HH
#define ODOMETER_HH

#include <PlayerStageControl/player/device/device.hh>

class Odometer : public Device {
public:
    Odometer(playerc_client_t *client);
    ~Odometer();

    // Gets
    Position getPosition();
    float getOrientation();
    bool isStall();

    // Sets
    void setSpeed(float x, float y, float theta);

private:
    playerc_position2d_t *_odometer;

    // Inheritance implementation (called by Player)
    friend class Player;
    bool connect();
    bool disconnect();
};

#endif // ODOMETER_HH
