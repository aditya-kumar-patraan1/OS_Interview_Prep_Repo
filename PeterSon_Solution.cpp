// while(1){
//     while(turn!=0) 
//     turn=1;
// }

// while(1){
//     while(turn!=1)
//     turn=0;
// }

// Peterson solution

// flag[2] = which process is ready to enter Critical Section
// turn = which process's turn is to enter Critical Section
flag[i]=ture //represents that process i is ready to enter CS


do{
    flag[0]=true;
    turn=1;
    while(turn==1 && flag[1]==true); //busy wait
    //critical section
    flag[0]=false;
    //remainder section
}while(1);


do{
    flag[1]=true;
    turn=0;
    while(turn==0 && flag[0]==true); //busy wait
    //critical section
    flag[1]=false;
}while(1);