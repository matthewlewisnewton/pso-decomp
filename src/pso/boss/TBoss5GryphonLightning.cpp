#include "pso/TBoss5GryphonLightning.h"
#include "pso/object/TObject_80019A50.h"

TBoss5GryphonLightning::~TBoss5GryphonLightning() {
    if (m_44 != nullptr) { queue_destruction__7TObjectFv(m_44); m_44 = nullptr; }
    if (m_40 != nullptr) { queue_destruction__7TObjectFv(m_40); m_40 = nullptr; }
    if (m_3c != nullptr) { queue_destruction__7TObjectFv(m_3c); m_3c = nullptr; }
    if (m_38 != nullptr) { queue_destruction__7TObjectFv(m_38); m_38 = nullptr; }
}
