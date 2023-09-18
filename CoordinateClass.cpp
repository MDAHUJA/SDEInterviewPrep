template <typename T, size_t Dimensions>
class Coordinate {
public:
    Coordinate() {
        // Initialize the coordinates to default values (0) for all dimensions.
        for (size_t i = 0; i < Dimensions; ++i) {
            coordinates[i] = T();
        }
    }

    // Setter and getter for individual dimensions
    void setDimension(size_t index, const T& value) {
        if (index < Dimensions) {
            coordinates[index] = value;
        }
    }

    T getDimension(size_t index) const {
        if (index < Dimensions) {
            return coordinates[index];
        }
        return T(); // Return a default value if the index is out of range.
    }

private:
    T coordinates[Dimensions];
};

int main() {
    // Create a 2D coordinate with integer values
    Coordinate<int, 2> point2D;
    point2D.setDimension(0, 3); // X-coordinate
    point2D.setDimension(1, 4); // Y-coordinate

    // Create a 3D coordinate with double values
    Coordinate<double, 3> point3D;
    point3D.setDimension(0, 1.5); // X-coordinate
    point3D.setDimension(1, 2.5); // Y-coordinate
    point3D.setDimension(2, 3.5); // Z-coordinate

    return 0;
}
