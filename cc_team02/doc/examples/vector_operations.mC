
void crossProduct(float[3] u, float[3] v, float[3] w)
{
    w[0] = (u[1]*v[2]) - (u[2]*v[1]);
    w[1] = (-u[0]*v[2]) + (u[2]*v[0]);
    w[2] = (u[0]*v[1]) - (u[1]*v[0]);
}

float dotProduct(float[3] u, float[3] v)
{
    return (u[0]*v[0]) + (u[1]*v[1]) + (u[2]*v[2]);
}

void mul(float[3] src, float k, float[3] dst)
{
    dst[0] = k*src[0];
    dst[1] = k*src[1];
    dst[2] = k*src[2];
}

void printVec(float[3] v)
{
    print_float(v[0]);
    print(",");
    print_float(v[1]);
    print(",");
    print_float(v[2]);
}

void main()
{
    float[3] a;
    float[3] b;
    float[3] c;

    print("Please enter three floating point numbers: ");
    a[0] = read_float();
    a[1] = read_float();
    a[2] = read_float();
    print_nl();

    b[0] = 1.0; b[1] = 1.0; b[2] = 1.0;
    c[0] = 0.0; c[1] = 0.0; c[2] = 0.0;

    print("The resulting cross product is: ");
    crossProduct(a,b,c);
    printVec(c);
    print_nl();

    print("The resulting dot product is: ");
    print_float(dotProduct(c,a));
    print_nl();

    print("The resulting multiplication is: ");
    mul(a,5.0,b);
    printVec(b);
    print_nl();
}
