int nxt[210];
void get_next(char *str)
{
     int i,j;
     i=0,j=-1;
     nxt[0]=-1;
     int n = strlen(str);
     while(i<n)
     {
          if(j==-1||str[i]==str[j])
          {
              i++;
              j++;
              nxt[i]=j;
          }    
          else
              j=nxt[j];
     } 
}
//ms为所求字符串
get_next(ms);
int n=strlen(ms);
//如果存在最小循环节
if(n%(n-nxt[n])==0){
	ans=lcm(ans,n-nxt[n]);
}
//不存在的情况
else{
	ans=lcm(ans,n);
}
