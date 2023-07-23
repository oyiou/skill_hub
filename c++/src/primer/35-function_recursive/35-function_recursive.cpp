//
// Created by leever on 6/15/2022.
//

int factorial(int val) {
    if(val > 1)
        return factorial(val - 1) * val;
    return 1;
}
int main() {
    return factorial(10);
}