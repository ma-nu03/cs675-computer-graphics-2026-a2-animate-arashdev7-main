#include "ihateumore.hpp"
#include "primitives.hpp"
#include "hierarchy_node.hpp"

namespace {
  const float PELVIS_W = 1.4f,  PELVIS_H = 0.35f, PELVIS_D = 0.8f;
  const float TORSO_W  = 1.4f,  TORSO_H  = 1.3f,  TORSO_D  = 0.8f;
  const float NECK_R   = 0.18f, NECK_H   = 0.15f;
  const float HEAD_R   = 0.5f,  HEAD_H   = 0.8f;
  const float ARM_W    = 0.4f,  ARM_L    = 0.95f, ARM_D    = 0.4f;
  const float HAND_R   = 0.22f, HAND_D   = 0.3f;
  const float LEG_W    = 0.68f, LEG_D    = 0.7f;
  const float THIGH_H  = 0.5f,  SHIN_H   = 0.4f;
  const float FOOT_H   = 0.2f,  FOOT_D   = 0.9f;
  const float HIP_X      = 0.35f;
  const float SHOULDER_X = TORSO_W/2 + ARM_W/2;     // arm sits flush against the torso
  const float SHOULDER_Y = TORSO_H - 0.05f;
  const float LEG_H      = THIGH_H + SHIN_H + FOOT_H;
}


MinifigStyle jokerStyle()
{
    MinifigStyle s;
    glm::vec4 purple(0.45f,0.15f,0.60f,1), dark(0.30f,0.10f,0.45f,1), white(0.95f,0.95f,0.95f,1);
    s.torso = purple; s.arms = purple;
    s.pelvis = dark;  s.legs = dark;  s.feet = glm::vec4(0.15f,0.05f,0.25f,1);
    s.hands = white;  s.neck = white; s.head = white;
    s.hair = glm::vec4(0.05f,0.60f,0.15f,1);
    s.hasHair = true;
    s.hasCape = false;
    s.face = FaceType::JOKER;
    return s;
}

MinifigStyle batmanStyle()
{
    MinifigStyle s;
    glm::vec4 suitBlack(0.06f,0.06f,0.08f,1), pureBlack(0.02f,0.02f,0.03f,1);
    s.torso = suitBlack; s.arms = suitBlack;
    s.pelvis = pureBlack; s.legs = pureBlack; s.feet = pureBlack;
    s.hands = pureBlack;  s.neck = pureBlack; s.head = pureBlack;
    s.hasHair = false;
    s.hasCape = true;
    s.capeColor = pureBlack;
    s.face = FaceType::BATMAN;
    return s;
}

void buildBatmanFace(std::vector<glm::vec4>& pos, std::vector<glm::vec4>& col)
{
    float z = HEAD_R + 0.02f;
    glm::vec4 skin(0.93f,0.76f,0.60f,1), eyeBlue(0.2f,0.85f,1.0f,1), black(0.02f,0.02f,0.03f,1);

    makeQuad(0.5f, 0.28f, glm::vec3(0, HEAD_H*0.22f, z), skin, pos, col);
    makeFlatArc(0.16f, 180.0f, 360.0f, glm::vec3(0, HEAD_H*0.22f, z+0.005f), 12, black, pos, col);

    makeSpike(glm::vec3(-0.10f, HEAD_H*0.95f, 0.10f), glm::vec3(-0.22f, HEAD_H*1.45f, -0.05f), 0.07f, black, pos, col);
    makeSpike(glm::vec3( 0.10f, HEAD_H*0.95f, 0.10f), glm::vec3( 0.22f, HEAD_H*1.45f, -0.05f), 0.07f, black, pos, col);

    makeFlatEllipse(0.11f, 0.05f, -18.0f, glm::vec3(-0.15f, HEAD_H*0.66f, z), 16, eyeBlue, pos, col);
    makeFlatEllipse(0.11f, 0.05f,  18.0f, glm::vec3( 0.15f, HEAD_H*0.66f, z), 16, eyeBlue, pos, col);
}

void buildJokerFace(std::vector<glm::vec4>& pos, std::vector<glm::vec4>& col)
{
    float z = HEAD_R + 0.02f;
    glm::vec4 black(0.05f,0.05f,0.05f,1), red(0.75f,0.05f,0.08f,1);
    glm::vec4 white(0.97f,0.97f,0.95f,1), green(0.05f,0.55f,0.15f,1);

    makeFlatEllipse(0.09f, 0.09f, 0.0f, glm::vec3(-0.15f, HEAD_H*0.66f, z), 14, black, pos, col);
    makeFlatEllipse(0.09f, 0.09f, 0.0f, glm::vec3( 0.15f, HEAD_H*0.66f, z), 14, black, pos, col);

    makeQuad(0.16f, 0.035f, glm::vec3(-0.15f, HEAD_H*0.80f, z), green, pos, col);
    makeQuad(0.16f, 0.035f, glm::vec3( 0.15f, HEAD_H*0.80f, z), green, pos, col);

    glm::vec3 mouthCenter(0, HEAD_H*0.32f, z);
    makeFlatArc(0.28f, 180.0f, 360.0f, mouthCenter, 16, red, pos, col);

    int nTeeth = 7;
    float toothW = 0.5f/nTeeth;
    for (int i = 0; i < nTeeth; ++i) {
        float x = mouthCenter.x - 0.25f + toothW*(i + 0.5f);
        makeFlatTriangleDown(glm::vec3(x, mouthCenter.y + 0.02f, z + 0.005f), toothW*0.9f, 0.09f, white, pos, col);
    }
}

void buildBatmanTorsoFront(std::vector<glm::vec4>& pos, std::vector<glm::vec4>& col)
{
    float z = TORSO_D/2 + 0.01f;
    glm::vec4 emblemBg(0.9f,0.75f,0.1f,1), emblemFg(0.02f,0.02f,0.03f,1), absColor(0.14f,0.14f,0.17f,1);

    makeBatEmblem(0.30f, glm::vec3(0, TORSO_H*0.62f, z), emblemBg, emblemFg, pos, col);

    float absTop = TORSO_H*0.45f, absBot = TORSO_H*0.10f, gap = 0.035f;
    float rowH = (absTop-absBot-2*gap)/3.0f, colHalfW = TORSO_W*0.16f;
    for (int row = 0; row < 3; ++row) {
        float yMid = absBot + row*(rowH+gap) + rowH/2;
        makeQuad(colHalfW, rowH, glm::vec3(-colHalfW/2-gap/2, yMid, z), absColor, pos, col);
        makeQuad(colHalfW, rowH, glm::vec3( colHalfW/2+gap/2, yMid, z), absColor, pos, col);
    }
}

void buildJokerTorsoFront(std::vector<glm::vec4>& pos, std::vector<glm::vec4>& col)
{
    float z = TORSO_D/2 + 0.01f;
    glm::vec4 shirtColor(0.9f,0.7f,0.1f,1), tieColor(0.1f,0.5f,0.2f,1);
    float shirtTop = TORSO_H*0.85f, shirtBot = TORSO_H*0.15f, yMid = (shirtTop+shirtBot)/2;

    makeQuad(TORSO_W*0.55f, shirtTop-shirtBot, glm::vec3(0, yMid, z), shirtColor, pos, col);
    makeQuad(0.12f, shirtTop-shirtBot, glm::vec3(0, yMid, z+0.005f), tieColor, pos, col);
}

Minifig buildMinifig(const MinifigStyle& s)
{
    using csX75::HNode;
    Minifig f;
    std::vector<glm::vec4> pos, col;

    // Turn whatever is currently in pos/col into a node, then empty them for the next part.
    auto part = [&](HNode* parent) {
        HNode* n = new HNode(parent, pos.size(), pos.data(), col.data(),
                             pos.size()*sizeof(glm::vec4), col.size()*sizeof(glm::vec4));
        pos.clear(); col.clear();
        return n;
    };
    // Put a node at its joint (relative to its parent) and remember that as the rest pose.
    auto place = [&](HNode* n, float x, float y, float z) {
        n->change_parameters(x, y, z, 0, 0, 0);
        n->save_defaults();
    };

    // ROOT: a pure joint. pos/col are empty, so it draws nothing.
    f.root = part(NULL);

    // PELVIS: spans y 0..PELVIS_H, so hips are at its bottom edge.
    makeCuboid(PELVIS_W, PELVIS_H, PELVIS_D, PELVIS_H, s.pelvis, pos, col);
    f.pelvis = part(f.root);
    place(f.pelvis, 0, LEG_H, 0);

    // TORSO
    makeCuboid(TORSO_W, TORSO_H, TORSO_D, TORSO_H, s.torso, pos, col);
    if (s.face == FaceType::BATMAN) buildBatmanTorsoFront(pos, col);
    if (s.face == FaceType::JOKER)  buildJokerTorsoFront(pos, col);
    f.torso = part(f.pelvis);
    place(f.torso, 0, PELVIS_H, 0);

    //cape(batman)
    if (s.hasCape) {
        makeCuboid(TORSO_W*0.9f, TORSO_H*1.3f, 0.06f, 0.0f, s.capeColor, pos, col);
        f.cape = part(f.torso);
        place(f.cape, 0, TORSO_H*0.95f, -(TORSO_D/2 + 0.03f));
        f.cape->set_rot_limits(-20,50, 0,0, 0,0);
    }

    // NECK: the joint that turns the head
    makeCylinder(NECK_R, NECK_H, 12, NECK_H, s.neck, pos, col);
    f.neck = part(f.torso);
    place(f.neck, 0, TORSO_H, 0);
    f.neck->set_rot_limits(-25,25, -90,90, 0,0);

    // HEAD (+ hair + character-specific face)
    makeCylinder(HEAD_R, HEAD_H, 24, HEAD_H, s.head, pos, col);
    if (s.hasHair) {
        makeHair(glm::vec3(0, HEAD_H - 0.43f, 0), 0.53f, 0.4f, 0.22f, 8, 20, 70.0f, s.hair, pos, col);
    }
    if (s.face == FaceType::BATMAN) buildBatmanFace(pos, col);
    if (s.face == FaceType::JOKER)  buildJokerFace(pos, col);
    f.head = part(f.neck);
    place(f.head, 0, NECK_H, 0);

    // ARMS + HANDS (i==0 is the figure's left, at +x)
    for (int i = 0; i < 2; ++i) {
        float sx = (i == 0) ? 1.0f : -1.0f;
        HNode*& arm  = (i == 0) ? f.lArm  : f.rArm;
        HNode*& hand = (i == 0) ? f.lHand : f.rHand;

        makeCuboid(ARM_W, ARM_L, ARM_D, 0.0f, s.arms, pos, col);
        arm = part(f.torso);
        place(arm, sx*SHOULDER_X, SHOULDER_Y, 0);
        arm->set_rot_limits(-180,60, 0,0, 0,0);

        makeClipHand(HAND_R, HAND_R*0.5f, HAND_D, 12, s.hands, pos, col);
        hand = part(arm);
        place(hand, 0, -ARM_L, 0);
        hand->set_rot_limits(0,0, -180,180, 0,0);
    }

    // LEGS: thigh (hip joint) -> shin (knee joint) -> foot (rigid, no ankle)
    for (int i = 0; i < 2; ++i) {
        float sx = (i == 0) ? 1.0f : -1.0f;
        HNode*& thigh = (i == 0) ? f.lThigh : f.rThigh;
        HNode*& shin  = (i == 0) ? f.lShin  : f.rShin;
        HNode*& foot  = (i == 0) ? f.lFoot  : f.rFoot;

        makeCuboid(LEG_W, THIGH_H, LEG_D, 0.0f, s.legs, pos, col);
        thigh = part(f.pelvis);
        place(thigh, sx*HIP_X, 0, 0);
        thigh->set_rot_limits(-90,30, 0,0, 0,0);

        makeCuboid(LEG_W, SHIN_H, LEG_D, 0.0f, s.legs, pos, col);
        shin = part(thigh);
        place(shin, 0, -THIGH_H, 0);
        shin->set_rot_limits(0,120, 0,0, 0,0);   // at 0 degrees thigh+shin look like one straight leg

        makeCuboid(LEG_W, FOOT_H, FOOT_D, 0.0f, s.feet, pos, col);
        foot = part(shin);
        place(foot, 0, -SHIN_H, 0.1f);           // shifted forward so the toe sticks out
        foot->set_rot_limits(0,0, 0,0, 0,0);
    }

    return f;
}