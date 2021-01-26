#include "ads/simulation/simulation_base.hpp"

namespace ads {

    simulation_base::simulation_base(const timesteps_config& steps)
    : steps{steps}
    { }

    void simulation_base::run() {
        before();
        for (int i = 0; i < steps.step_count; ++ i) {
            double t = i * steps.dt;
            before_step(i, t);
            step(i, t);
            after_step(i, t);
        }
        after();
    }

}
