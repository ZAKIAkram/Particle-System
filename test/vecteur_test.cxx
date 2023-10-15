#include <gtest/gtest.h>
#include "../include/Vecteur.hxx"

// Test for the default constructor
TEST(VecteurTest, DefaultConstructor) {
    Vecteur vec;
    EXPECT_EQ(vec.getDim(), 0);
}

// Test for the constructor with dimension parameter
TEST(VecteurTest, DimensionConstructor) {
    int dim = 3;
    Vecteur vec(dim);
    EXPECT_EQ(vec.getDim(), dim);
    std::vector<double> values = vec.getValues();
    EXPECT_EQ(values.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(values[i], 0.0);
    }
}

// Test for the constructor with dimension and values array parameters
TEST(VecteurTest, ArrayConstructor) {
    int dim = 3;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);
    EXPECT_EQ(vec.getDim(), dim);
    std::vector<double> vecValues = vec.getValues();
    EXPECT_EQ(vecValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(vecValues[i], values[i]);
    }
}

// Test for the setI() method
TEST(VecteurTest, SetValue) {
    int dim = 3;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);

    double newValue = 5.0;
    int index = 1;
    vec.setI(index, newValue);

    EXPECT_EQ(vec[index], newValue);
}

// Test for the += operator
TEST(VecteurTest, AdditionAssignmentOperator) {
    int dim = 3;
    double values1[dim] = {1.0, 2.0, 3.0};
    double values2[dim] = {4.0, 5.0, 6.0};
    Vecteur vec1(dim, values1);
    Vecteur vec2(dim, values2);

    vec1 += vec2;

    std::vector<double> resultValues = vec1.getValues();
    EXPECT_EQ(resultValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues[i], values1[i] + values2[i]);
    }
}

// Test for the -= operator
TEST(VecteurTest, SubtractionAssignmentOperator) {
    int dim = 3;
    double values1[dim] = {4.0, 5.0, 6.0};
    double values2[dim] = {1.0, 2.0, 3.0};
    Vecteur vec1(dim, values1);
    Vecteur vec2(dim, values2);

    vec1 -= vec2;

    std::vector<double> resultValues = vec1.getValues();
    EXPECT_EQ(resultValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues[i], values1[i] - values2[i]);
    }
}

// Test for the scalar multiplication operator *
TEST(VecteurTest, ScalarMultiplicationOperator) {
    int dim = 3;
    double k = 2.0;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);

    Vecteur result = vec * k;

    std::vector<double> resultValues = result.getValues();
    EXPECT_EQ(resultValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues[i], values[i] * k);
    }
}

// Test for element access using []
TEST(VecteurTest, ElementAccess) {
    int dim = 3;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);

    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(vec[i], values[i]);
    }
}

// Test for const element access using []
TEST(VecteurTest, ConstElementAccess) {
    int dim = 3;
    double values[dim] = {1.0, 2.0, 3.0};
    const Vecteur vec(dim, values);

    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(vec[i], values[i]);
    }
}

// Test for the output operator <<
TEST(VecteurTest, OutputOperator) {
    int dim = 3;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);

    std::stringstream ss;
    ss << vec;

    std::string expectedOutput = "1.000000 2.000000 3.000000 ";
    EXPECT_EQ(ss.str(), expectedOutput);
}

// Test for scalar-vector multiplication operator *
TEST(VecteurTest, ScalarVectorMultiplication) {
    int dim = 3;
    double k = 2.0;
    double values[dim] = {1.0, 2.0, 3.0};
    Vecteur vec(dim, values);

    Vecteur result1 = k * vec;
    Vecteur result2 = vec * k;

    std::vector<double> resultValues1 = result1.getValues();
    std::vector<double> resultValues2 = result2.getValues();
    EXPECT_EQ(resultValues1.size(), dim);
    EXPECT_EQ(resultValues2.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues1[i], values[i] * k);
        EXPECT_EQ(resultValues2[i], values[i] * k);
    }
}

// Test for vector addition operator +
TEST(VecteurTest, VectorAddition) {
    int dim = 3;
    double values1[dim] = {1.0, 2.0, 3.0};
    double values2[dim] = {4.0, 5.0, 6.0};
    Vecteur vec1(dim, values1);
    Vecteur vec2(dim, values2);

    Vecteur result = vec1 + vec2;

    std::vector<double> resultValues = result.getValues();
    EXPECT_EQ(resultValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues[i], values1[i] + values2[i]);
    }
}

// Test for vector subtraction operator -
TEST(VecteurTest, VectorSubtraction) {
    int dim = 3;
    double values1[dim] = {4.0, 5.0, 6.0};
    double values2[dim] = {1.0, 2.0, 3.0};
    Vecteur vec1(dim, values1);
    Vecteur vec2(dim, values2);

    Vecteur result = vec1 - vec2;

    std::vector<double> resultValues = result.getValues();
    EXPECT_EQ(resultValues.size(), dim);
    for (int i = 0; i < dim; i++) {
        EXPECT_EQ(resultValues[i], values1[i] - values2[i]);
    }
}
