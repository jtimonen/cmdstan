#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>
#include <algorithm>

class Models_BasicDistributions_Triangle : 
  public Model_Test_Fixture<Models_BasicDistributions_Triangle> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("stan");
    model_path.push_back("src");
    model_path.push_back("models");
    model_path.push_back("basic_distributions");
    model_path.push_back("triangle");
    return model_path;
  }
  static bool has_data() {
    return false;
  }

  static bool has_init() {
    return false;
  }

  static int num_iterations() {
    return iterations;
  }

  static std::vector<int> skip_chains_test() {
    std::vector<int> params_to_skip;
    return params_to_skip;
  }

  static void populate_chains() {
    default_populate_chains();
  }

  static std::vector<std::pair<int, double> >
  get_expected_values() {
    using std::make_pair;
    std::vector<std::pair<int, double> > expected_values;
    
    expected_values.push_back(make_pair(chains->index("y"), 0));
    
    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BasicDistributions_Triangle,
            Model_Test_Fixture,
            Models_BasicDistributions_Triangle);

TEST_F(Models_BasicDistributions_Triangle,
  Test_Triangle) {
  populate_chains();
  
  Eigen::VectorXd y = chains->samples(chains->index("y"));

  EXPECT_LE(y.minCoeff(), -0.9)
    << "expecting to get close to the corner";
  EXPECT_GE(y.maxCoeff(), 0.9)
    << "expecting to get close to the corner";
}

