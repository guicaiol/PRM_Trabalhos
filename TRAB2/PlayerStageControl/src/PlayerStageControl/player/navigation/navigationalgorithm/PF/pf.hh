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

#ifndef PF_HH
#define PH_HH

#include <PlayerStageControl/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <PlayerStageControl/utils/vector/vector.hh>

class PF : public NavigationAlgorithm {
public:
    PF();

    void reset();
    void setOrigin(const Position &origin);
    void setGoal(const Position &goa);
    void addObstacle(const Position &obst);
    float getDirection();
private:
    // Forces
    void addRepulsive(const Vector &v, float k);
    void addAttractive(const Vector &v);
    void addForce(const Vector &v);

    // Distance function
    Vector applyDistanceFunction(Vector v, float k);

    // Auxiliary functions
    static Vector getVector(const Position &v1, const Position &v2);

    // Goal and origin
    Position _origin;
    Position _goal;

    // Resultant force
    Vector _resultantForce;
};

#endif // PH_HH
