


void hanoi_nex(int n,int from,char temp,char to){
	if(n==1)
	{
		move(from,temp);
		cnt2++;
		move(temp,to);
		cnt2++;
	}
	else{
		hanoi_nex(n-1,from,temp,to);
		move(from,temp);
		cnt2++; 
		hanoi_nex(n-1,to,temp,from);
		move(temp,to);
		cnt2++;
		hanoi_nex(n-1,from,temp,to);
	}
}


