class Triangle {
private:
    double x1, y1;
    double x2, y2;
    double x3, y3;

    double distance(double xA, double yA, double xB, double yB) const;

public:
    Triangle(double x1, double y1,
        double x2, double y2,
        double x3, double y3);

    double getInRadius() const;
    void print() const;

    ~Triangle();
};





