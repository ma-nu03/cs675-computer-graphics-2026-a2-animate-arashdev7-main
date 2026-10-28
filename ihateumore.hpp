#ifndef _IHATEUMORE_HPP_
#define _IHATEUMORE_HPP_

#include "hierarchy_node.hpp"

enum class FaceType { PLAIN, BATMAN, JOKER };

// Everything that differs between two characters: just colours (and whether there's hair).
struct MinifigStyle {
    glm::vec4 torso, pelvis, arms, hands, legs, feet, neck, head, hair;
    bool hasHair;
    bool hasCape;
    glm::vec4 capeColor;
    FaceType face;
};

// Handles to every node, so the key callback can pick any joint.
struct Minifig {
    csX75::HNode *root, *pelvis, *torso, *neck, *head;
    csX75::HNode *lArm, *rArm, *lHand, *rHand;
    csX75::HNode *lThigh, *rThigh, *lShin, *rShin, *lFoot, *rFoot;
    csX75::HNode *cape;
};

MinifigStyle jokerStyle();
MinifigStyle batmanStyle();
Minifig buildMinifig(const MinifigStyle& s);

#endif