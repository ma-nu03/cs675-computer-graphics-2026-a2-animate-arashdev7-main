#ifndef _PRIMITIVES_HPP_
#define _PRIMITIVES_HPP_
// Ok, so we are building primitive shapes for the 3d model, This hpp file is essentially built for declarations and the actual shit happens in the cpp file.
// It has 2 output vectors so it can be used to make weird shapes meshed together. More on this later
#include <vector>
#include "glm/vec3.hpp" 
#include "glm/vec4.hpp"

// A box. pivotY=0 means the box hangs DOWN from y=0 to y=-h
// (good for arms/legs pivoting at a joint). pivotY=h/2 centers it on the origin
// (good for torso/pelvis). essentially a cuboid innit
void makeCuboid(float w, float h, float d, float pivotY, glm::vec4 color,
                 std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// One triangular spike (a thin 4-faced pyramid), used to build spiky hair for JOKER, our yoai in desperate need of attention 
void makeSpike(glm::vec3 base, glm::vec3 tip, float width, glm::vec4 color,
                std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// An arm with a fixed (non-jointed) bend baked into the mesh, per our Option B decision.
void makeBentArm(float upperLen, float lowerLen, float w, float d, float bendDeg,
                  glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);   

void makeCylinder(float radius, float h, int slices, float pivotY, glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);              

                  void makeCylinder(float radius, float h, int slices, float pivotY, glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

void makeClipHand(float outerR, float innerR, float depth, int slices, glm::vec4 color,
                  std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

void makeHair(glm::vec3 headCenter, float headRadius, float spikeLength, float spikeWidth,
              int numRings, int basePhiCount, float maxThetaDeg,
              glm::vec4 color,
              std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A flat rectangle, facing +z, centered at 'center'.
void makeQuad(float w, float h, glm::vec3 center, glm::vec4 color,
              std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A flat filled circle, facing +z.
void makeFlatDisc(float radius, glm::vec3 center, int slices, glm::vec4 color,
                   std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A flat pie-slice arc. E.g. startDeg=180, endDeg=360 sweeps the BOTTOM half of a circle:
// straight flat edge along the top, curved edge along the bottom. Facing +z.
void makeFlatArc(float radius, float startDeg, float endDeg, glm::vec3 center, int slices,
                  glm::vec4 color, std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A flat ellipse, facing +z, tilted by tiltDeg (positive = counter-clockwise).
void makeFlatEllipse(float radiusX, float radiusY, float tiltDeg, glm::vec3 center, int slices,
                      glm::vec4 color, std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A single flat triangle pointing DOWN from topCenter (flat edge on top). Used for teeth.
void makeFlatTriangleDown(glm::vec3 topCenter, float w, float h, glm::vec4 color,
                           std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);

// A rough low-poly bat-silhouette badge: a rectangular background plus a bat shape on top.
void makeBatEmblem(float size, glm::vec3 center, glm::vec4 bg, glm::vec4 fg,
                    std::vector<glm::vec4>& outPos, std::vector<glm::vec4>& outCol);
                                  
#endif