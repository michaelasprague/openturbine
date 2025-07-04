#include <array>
#include <vector>

#include <gtest/gtest.h>

#include "elements/beams/beam_quadrature.hpp"

namespace openturbine::tests {

TEST(BeamQuadratureTest, CheckCreateTrapezoidalQuadrature_1) {
    const auto q_act = CreateTrapezoidalQuadrature({0., 0.2, 0.4, 0.6, 0.8, 1.0});
    const BeamQuadrature q_exp{
        {-1., 0.2}, {-0.6, 0.4}, {-0.2, 0.4}, {0.2, 0.4}, {0.6, 0.4}, {1., 0.2},
    };
    for (auto i = 0U; i < q_exp.size(); ++i) {
        for (auto j = 0U; j < 2U; ++j) {
            EXPECT_NEAR(q_act[i][j], q_exp[i][j], 1e-14);
        }
    }
}

TEST(BeamQuadratureTest, CheckCreateTrapezoidalQuadrature_2) {
    const auto q_act = CreateTrapezoidalQuadrature({-5., -3., -1., 0., 3., 4., 5.});
    const BeamQuadrature q_exp{
        {-1., 0.2}, {-0.6, 0.4}, {-0.2, 0.3}, {0., 0.4}, {0.6, 0.4}, {0.8, 0.2}, {1., 0.1},
    };
    for (auto i = 0U; i < q_exp.size(); ++i) {
        for (auto j = 0U; j < 2U; ++j) {
            EXPECT_NEAR(q_act[i][j], q_exp[i][j], 1e-14);
        }
    }
}

}  // namespace openturbine::tests
