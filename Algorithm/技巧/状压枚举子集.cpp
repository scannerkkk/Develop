for (int S=1; S<(1<<n); ++S){
    for (int S0=(S-1)&S; S0; S0=(S0-1)&S)
        //do something.
}
