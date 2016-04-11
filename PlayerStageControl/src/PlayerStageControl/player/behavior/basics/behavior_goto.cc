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

#include "behavior_goto.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

Behavior_GoTo::Behavior_GoTo() {

}

void Behavior_GoTo::run() {
    player()->goToLookTo(_destination, _posToLook, true);


    std::cout << "state: " << player()->gripper()->state() << "\n";

    if(player()->isAtPosition(_destination)) {
        player()->gripper()->close();
    } else {
        player()->gripper()->open();
    }

//    std::cout << "position: x=" << player()->position().x() << ", y=" << player()->position().y() << ", a=" << Utils::toDegree(player()->orientation()) << "\n";
}
