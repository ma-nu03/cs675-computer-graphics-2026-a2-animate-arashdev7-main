#include "primitives.hpp"
#include <cmath>
#include <algorithm>
#include "glm/trigonometric.hpp"

void makeCuboid(float w, float h, float d, float pivotY, glm::vec4 color,
                 std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    // Work out the 6 boundary planes of the box from its size and pivot.
    float x0 = -w/2, x1 = w/2;            // centered on x
    float y0 = pivotY - h, y1 = pivotY;   // top at pivotY, extends down by h
    float z0 = -d/2, z1 = d/2;            // centered on z

    // The 8 corners, same layout/order as colorcube()'s positions[8]
    glm::vec4 p[8] = {
        {x0,y0,z1,1}, {x0,y1,z1,1}, {x1,y1,z1,1}, {x1,y0,z1,1},  // front face: 0,1,2,3
        {x0,y0,z0,1}, {x0,y1,z0,1}, {x1,y1,z0,1}, {x1,y0,z0,1}   // back face:  4,5,6,7
    };

    // Local helper: exactly Tutorial 2's quad(), but writing into our vectors
    // instead of the global v_positions/v_colors arrays.
    auto quad = [&](int a, int b, int c, int d_) {
        int idx[6] = {a,b,c, a,c,d_};
        for (int i : idx) { outPos.push_back(p[i]); outCol.push_back(color); }
    };

    quad(1,0,3,2); quad(2,3,7,6); quad(3,0,4,7);
    quad(6,5,1,2); quad(4,5,6,7); quad(5,4,0,1);
}

void makeSpike(glm::vec3 base, glm::vec3 tip, float width, glm::vec4 color,
                std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    // 3 points spread around 'base' forming a small triangle (the spike's root)
    glm::vec3 b1 = base + glm::vec3(width, 0, 0);
    glm::vec3 b2 = base + glm::vec3(-width/2, 0,  width*0.87f);
    glm::vec3 b3 = base + glm::vec3(-width/2, 0, -width*0.87f);

    auto push = [&](glm::vec3 v){ outPos.push_back(glm::vec4(v,1)); outCol.push_back(color); };

    push(b1); push(b2); push(b3);   // base triangle (closes the bottom)
    push(b1); push(b2); push(tip);  // 3 side faces, each a triangle from
    push(b2); push(b3); push(tip);  // one base edge up to the shared tip
    push(b3); push(b1); push(tip);
}

void makeClipHand(float outerR, float innerR, float depth, int slices, glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float cy = -outerR;   // shifts the ring so its topmost point sits at y=0 (the wrist)
    float zA = -depth/2, zB = depth/2;
    auto push = [&](float x, float y, float z){
        outPos.push_back(glm::vec4(x, y, z, 1)); outCol.push_back(color);
    };
    auto Pout = [&](float a, float z){ return glm::vec3(outerR*cos(a), cy + outerR*sin(a), z); };
    auto Pin  = [&](float a, float z){ return glm::vec3(innerR*cos(a), cy + innerR*sin(a), z); };

    for (int i = 0; i < slices; ++i) {
        float a0 = M_PI*i/slices, a1 = M_PI*(i+1)/slices;
        glm::vec3 o0a=Pout(a0,zA), o0b=Pout(a0,zB), o1a=Pout(a1,zA), o1b=Pout(a1,zB);
        glm::vec3 n0a=Pin (a0,zA), n0b=Pin (a0,zB), n1a=Pin (a1,zA), n1b=Pin (a1,zB);

        // outer curved wall
        push(o0a.x,o0a.y,o0a.z); push(o0b.x,o0b.y,o0b.z); push(o1b.x,o1b.y,o1b.z);
        push(o0a.x,o0a.y,o0a.z); push(o1b.x,o1b.y,o1b.z); push(o1a.x,o1a.y,o1a.z);
        // inner curved wall (the hollow bore)
        push(n0a.x,n0a.y,n0a.z); push(n1b.x,n1b.y,n1b.z); push(n0b.x,n0b.y,n0b.z);
        push(n0a.x,n0a.y,n0a.z); push(n1a.x,n1a.y,n1a.z); push(n1b.x,n1b.y,n1b.z);
        // top rim (z=zB), the flat ring-shaped strip between outer and inner
        push(o0b.x,o0b.y,o0b.z); push(n0b.x,n0b.y,n0b.z); push(n1b.x,n1b.y,n1b.z);
        push(o0b.x,o0b.y,o0b.z); push(n1b.x,n1b.y,n1b.z); push(o1b.x,o1b.y,o1b.z);
        // bottom rim (z=zA)
        push(o0a.x,o0a.y,o0a.z); push(n1a.x,n1a.y,n1a.z); push(n0a.x,n0a.y,n0a.z);
        push(o0a.x,o0a.y,o0a.z); push(o1a.x,o1a.y,o1a.z); push(n1a.x,n1a.y,n1a.z);
    }

    // flat end caps at each open end of the "C", so the hollow arc doesn't look see-through
    glm::vec3 A_oa=Pout(0,zA), A_ob=Pout(0,zB), A_ia=Pin(0,zA), A_ib=Pin(0,zB);
    push(A_oa.x,A_oa.y,A_oa.z); push(A_ob.x,A_ob.y,A_ob.z); push(A_ib.x,A_ib.y,A_ib.z);
    push(A_oa.x,A_oa.y,A_oa.z); push(A_ib.x,A_ib.y,A_ib.z); push(A_ia.x,A_ia.y,A_ia.z);

    glm::vec3 B_oa=Pout(M_PI,zA), B_ob=Pout(M_PI,zB), B_ia=Pin(M_PI,zA), B_ib=Pin(M_PI,zB);
    push(B_oa.x,B_oa.y,B_oa.z); push(B_ib.x,B_ib.y,B_ib.z); push(B_ob.x,B_ob.y,B_ob.z);
    push(B_oa.x,B_oa.y,B_oa.z); push(B_ia.x,B_ia.y,B_ia.z); push(B_ib.x,B_ib.y,B_ib.z);
}

void makeHair(glm::vec3 headCenter, float headRadius, float spikeLength, float spikeWidth,
              int numRings, int basePhiCount, float maxThetaDeg,
              glm::vec4 color,
              std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float maxTheta = glm::radians(maxThetaDeg);

    for (int r = 0; r < numRings; ++r) {
        float t = (float)(r + 1) / numRings;
        float theta = t * maxTheta;
        int spikesInRing = std::max(3, (int)(basePhiCount * sin(theta) / sin(maxTheta)));

        for (int i = 0; i < spikesInRing; ++i) {
            float phi = 2*M_PI*i/spikesInRing;
            glm::vec3 dir(sin(theta)*cos(phi), cos(theta), sin(theta)*sin(phi));
            glm::vec3 base = headCenter + headRadius * dir;
            glm::vec3 tip  = base + spikeLength * dir;
            makeSpike(base, tip, spikeWidth, color, outPos, outCol);
        }
    }
}


#include "glm/gtc/matrix_transform.hpp"

void makeBentArm(float upperLen, float lowerLen, float w, float d, float bendDeg,
                  glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    // Upper segment: hangs from the shoulder (pivot 0) down to -upperLen
    makeCuboid(w, upperLen, d, 0.0f, color, outPos, outCol);

    // Lower segment: build it hanging from its OWN local 0, then bake in
    // the fixed bend by transforming its vertices before appending them.
    std::vector<glm::vec4> lowerPos, lowerCol;
    makeCuboid(w, lowerLen, d, 0.0f, color, lowerPos, lowerCol);

    glm::mat4 bend = glm::translate(glm::mat4(1.0f), glm::vec3(0, -upperLen, 0))
                    * glm::rotate(glm::mat4(1.0f), glm::radians(bendDeg), glm::vec3(0,0,1));

    for (auto& v : lowerPos) v = bend * v;   // apply the fixed offset+rotation to every vertex

    outPos.insert(outPos.end(), lowerPos.begin(), lowerPos.end());
    outCol.insert(outCol.end(), lowerCol.begin(), lowerCol.end());
}

// Same pivotY convention as makeCuboid: pivotY is the y of the TOP face,
// and the cylinder extends downward by h.
void makeCylinder(float radius, float h, int slices, float pivotY, glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float yTop = pivotY, yBot = pivotY - h;
    auto push = [&](float x, float y, float z){
        outPos.push_back(glm::vec4(x, y, z, 1)); outCol.push_back(color);
    };

    for (int i = 0; i < slices; ++i) {
        float a0 = 2*M_PI*i/slices, a1 = 2*M_PI*(i+1)/slices;
        float x0 = radius*cos(a0), z0 = radius*sin(a0);
        float x1 = radius*cos(a1), z1 = radius*sin(a1);

        // side wall: one rectangle = 2 triangles
        push(x0,yTop,z0); push(x0,yBot,z0); push(x1,yBot,z1);
        push(x0,yTop,z0); push(x1,yBot,z1); push(x1,yTop,z1);
        // one slice of the top cap: a triangle from the centre to the rim
        push(0,yTop,0);   push(x1,yTop,z1); push(x0,yTop,z0);
        // one slice of the bottom cap
        push(0,yBot,0);   push(x0,yBot,z0); push(x1,yBot,z1);
    }
}

void makeQuad(float w, float h, glm::vec3 center, glm::vec4 color,
              std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float x0=center.x-w/2, x1=center.x+w/2, y0=center.y-h/2, y1=center.y+h/2, z=center.z;
    auto push=[&](float x,float y){ outPos.push_back(glm::vec4(x,y,z,1)); outCol.push_back(color); };
    push(x0,y0); push(x1,y0); push(x1,y1);
    push(x0,y0); push(x1,y1); push(x0,y1);
}

void makeFlatDisc(float radius, glm::vec3 center, int slices, glm::vec4 color,
                   std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    auto push=[&](float x,float y){ outPos.push_back(glm::vec4(x,y,center.z,1)); outCol.push_back(color); };
    for (int i = 0; i < slices; ++i) {
        float a0=2*M_PI*i/slices, a1=2*M_PI*(i+1)/slices;
        push(center.x,center.y);
        push(center.x+radius*cos(a0), center.y+radius*sin(a0));
        push(center.x+radius*cos(a1), center.y+radius*sin(a1));
    }
}

void makeFlatArc(float radius, float startDeg, float endDeg, glm::vec3 center, int slices,
                  glm::vec4 color, std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float a0 = glm::radians(startDeg), a1 = glm::radians(endDeg);
    auto push=[&](float x,float y){ outPos.push_back(glm::vec4(center.x+x,center.y+y,center.z,1)); outCol.push_back(color); };
    for (int i = 0; i < slices; ++i) {
        float t0 = a0 + (a1-a0)*i/slices, t1 = a0 + (a1-a0)*(i+1)/slices;
        push(0,0);
        push(radius*cos(t0), radius*sin(t0));
        push(radius*cos(t1), radius*sin(t1));
    }
}

void makeFlatEllipse(float radiusX, float radiusY, float tiltDeg, glm::vec3 center, int slices,
                      glm::vec4 color, std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    float t = glm::radians(tiltDeg), ct = cos(t), st = sin(t);
    auto push=[&](float ex,float ey){
        float x = ex*ct - ey*st, y = ex*st + ey*ct;
        outPos.push_back(glm::vec4(center.x+x, center.y+y, center.z, 1));
        outCol.push_back(color);
    };
    for (int i = 0; i < slices; ++i) {
        float a0 = 2*M_PI*i/slices, a1 = 2*M_PI*(i+1)/slices;
        push(0,0);
        push(radiusX*cos(a0), radiusY*sin(a0));
        push(radiusX*cos(a1), radiusY*sin(a1));
    }
}

void makeFlatTriangleDown(glm::vec3 topCenter, float w, float h, glm::vec4 color,
                           std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    glm::vec3 tl = topCenter + glm::vec3(-w/2, 0, 0);
    glm::vec3 tr = topCenter + glm::vec3( w/2, 0, 0);
    glm::vec3 bot= topCenter + glm::vec3(0, -h, 0);
    outPos.push_back(glm::vec4(tl,1)); outCol.push_back(color);
    outPos.push_back(glm::vec4(tr,1)); outCol.push_back(color);
    outPos.push_back(glm::vec4(bot,1)); outCol.push_back(color);
}

void makeBatEmblem(float size, glm::vec3 center, glm::vec4 bg, glm::vec4 fg,
                    std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol)
{
    makeQuad(size*1.3f, size*0.9f, center, bg, outPos, outCol);

    float z = center.z + 0.005f;
    auto push=[&](float x,float y){ outPos.push_back(glm::vec4(center.x+x,center.y+y,z,1)); outCol.push_back(fg); };
    float s = size;
    push(-0.05f*s,-0.3f*s); push(0.05f*s,-0.3f*s); push(0.0f,0.35f*s);
    push(-0.05f*s,-0.1f*s); push(-0.6f*s,0.15f*s); push(-0.15f*s,0.1f*s);
    push(-0.05f*s,-0.1f*s); push(-0.15f*s,0.1f*s); push(-0.05f*s,0.2f*s);
    push(0.05f*s,-0.1f*s); push(0.15f*s,0.1f*s); push(0.6f*s,0.15f*s);
    push(0.05f*s,-0.1f*s); push(0.05f*s,0.2f*s); push(0.15f*s,0.1f*s);
}