int switch_test(int x)
{
    int result;
    switch(x) {
        case 1:
            result = 100;
            break;
        case 2:
            result = 200;
            break;
        case 3:
            result = 300;
            break;
        default:
            result = 0;
    }
    return result;
}
