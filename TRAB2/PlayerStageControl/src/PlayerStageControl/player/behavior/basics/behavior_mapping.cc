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

#include "behavior_mapping.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

#define RESOLUTION 0.025 // m
#define MAP_X_MIN -8.0
#define MAP_X_MAX  8.0
#define MAP_Y_MIN -8.0
#define MAP_Y_MAX  8.0

#define RGB_MAX 255

Behavior_Mapping::Behavior_Mapping() {
    _width = (MAP_X_MAX-MAP_X_MIN)/RESOLUTION;
    _height = (MAP_Y_MAX-MAP_Y_MIN)/RESOLUTION;

    std::cout << "width: " << _width << "\n";
    std::cout << "height: " << _width << "\n";

    // Create map
    _map.resize(_height);
    for(unsigned i=0; i<_map.size(); i++)
        _map.at(i).resize(_width, 0.5);

    // Create OpenCV image
    _image = cvCreateImage(cvSize(_width,_height), IPL_DEPTH_8U, 3);
    refreshView();
}

Behavior_Mapping::~Behavior_Mapping() {

}

void Behavior_Mapping::run() {
    // Player moviment
    player()->idle();

    // Reset view
//    resetView();

    // Player laser mapping
    Laser *laser = player()->laser();
    for(int i=0; i<laser->getScanCount(); i++) {
        const float range = laser->getRange(i);
        const float bearing = laser->getBearing(i);

        // Draw lines
        float globalAngle = player()->orientation() + bearing;
        Position relPos(range*cos(globalAngle), range*sin(globalAngle));
        Position pos(player()->position().x() + relPos.x(), player()->position().y() + relPos.y());
        drawLine(player()->position(), pos);

        // Point
        if(range < laser->getMaxRange())
            drawPosition(pos, RGB_MAX, 0, 0);
    }



    // Update map to view
    updateMapToView();

    // Refresh
    refreshView();
}

void Behavior_Mapping::resetView() {
    cvSet(_image, cvScalar(0,0,0));
}

void Behavior_Mapping::refreshView() {
    cvNamedWindow("Behavior_Mapping", 1);
    cvShowImage("Behavior_Mapping", _image);
    cvWaitKey(50);
}

void Behavior_Mapping::updateMapToView() {

}

void Behavior_Mapping::drawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if(x>=0 && y>=0 && x<=_width && y<=_height) {
        _image->imageData[3*((y*_width)+x)]   = b;
        _image->imageData[3*((y*_width)+x)+1] = g;
        _image->imageData[3*((y*_width)+x)+2] = r;
    }
}

void Behavior_Mapping::drawPosition(const Position &pos, unsigned char r,  unsigned char g, unsigned char b) {
    const int x = (pos.x()+MAP_X_MAX)/RESOLUTION;
    const int y = _height - (pos.y()+MAP_Y_MAX)/RESOLUTION;
    drawPixel(x, y, r, g, b);
}

void Behavior_Mapping::drawLine(const Position &p1, const Position &p2) {
    const int x1 = (p1.x()+MAP_X_MAX)/RESOLUTION;
    const int y1 = _height - (p1.y()+MAP_Y_MAX)/RESOLUTION;
    const int x2 = (p2.x()+MAP_X_MAX)/RESOLUTION;
    const int y2 = _height - (p2.y()+MAP_Y_MAX)/RESOLUTION;

    int slope;
    int dx, dy, incE, incNE, d, x, y;

    // Onde inverte a linha x1 > x2
    if (x1 > x2) {
        drawLine(p2, p1);
        return;
    }
    dx = x2 - x1;
    dy = y2 - y1;

    if (dy < 0) {
        slope = -1;
        dy = -dy;
    } else {
        slope = 1;
    }

    // Constante de Bresenham
    incE = 2 * dy;
    incNE = 2 * dy - 2 * dx;
    d = 2 * dy - dx;
    y = y1;
    for (x = x1; x <= x2; x++){
        drawPixel(x, y, RGB_MAX, RGB_MAX, RGB_MAX);

        if (d <= 0) {
            d += incE;
        } else {
            d += incNE;
            y += slope;
        }
    }
}