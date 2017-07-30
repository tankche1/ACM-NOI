var
s,left,right,fa,size:array[0..150000] of int64;
a:array[0..150000] of int64;
sum,root,ans,m,kk,p:int64;
i:longint;
{-------------}
function min(x,y:int64):int64;
begin
if x<y then exit(x) else exit(y);
end;
{-------------}
procedure left_r(x:longint);
var
i:longint;
begin
i:=fa[x];

fa[x]:=fa[i];
if i=left[fa[i]] then left[fa[i]]:=x else right[fa[i]]:=x;

fa[right[x]]:=i;
left[i]:=right[x];

fa[i]:=x;
right[x]:=i;

size[i]:=size[left[i]]+size[right[i]]+1;
size[x]:=size[left[x]]+size[right[x]]+1;

s[i]:=s[left[i]]+s[right[i]]+a[i];
s[x]:=s[left[x]]+s[right[x]]+a[x];
end;
{-------------}
procedure right_r(x:longint);
var
i:longint;
begin
i:=fa[x];

fa[x]:=fa[i];
if i=left[fa[i]] then left[fa[i]]:=x else right[fa[i]]:=x;

fa[left[x]]:=i;
right[i]:=left[x];

fa[i]:=x;
left[x]:=i;

size[i]:=size[left[i]]+size[right[i]]+1;
size[x]:=size[left[x]]+size[right[x]]+1;

s[i]:=s[left[i]]+s[right[i]]+a[i];
s[x]:=s[left[x]]+s[right[x]]+a[x];
end;
{-------------}
procedure splay(x,y:longint);
var
i,up,down:int64;
begin
if (fa[x]=y) or (x=y) then exit;
i:=fa[x];
while (fa[i]<>y) and (fa[x]<>y) do
  begin
  if x=left[fa[x]] then down:=1 else down:=-1;
  if i=left[fa[i]] then up:=1 else up:=-1;
  if up*down=1 then
    begin
    if up=1 then
      begin
      left_r(i);
      left_r(x);
      end
    else
      begin
      right_r(i);
      right_r(x);
      end;
    end
  else
    begin
    if down=1 then
      begin
      left_r(x);
      right_r(x);
      end
    else
      begin
      right_r(x);
      left_r(x);
      end;
    end;
  i:=fa[x];
  end;

if fa[x]<>y then
  if x=left[fa[x]] then left_r(x) else right_r(x);
end;
{-------------}
procedure insert(x:longint);
var
i:int64;
begin
i:=root;
if i=0 then
  begin
  inc(sum);
  size[sum]:=1;
  a[sum]:=x;
  root:=sum;
  exit;
  end;

while true do
  begin
  if x>a[i] then
    begin
    if right[i]=0 then
      begin
          size[i]:=size[i]+1;
          s[i]:=s[i]+x;
      inc(sum);
      right[i]:=sum;
      fa[sum]:=i;
      a[sum]:=x;
      break;
      end
    else
          begin
          inc(size[i]);
          s[i]:=s[i]+x;
      i:=right[i];
          end;
    end
  else
    begin
    if left[i]=0 then
      begin
          size[i]:=size[i]+1;
          s[i]:=s[i]+x;
      inc(sum);
      left[i]:=sum;
      fa[sum]:=i;
      a[sum]:=x;
      break;
      end
    else
          begin
          inc(size[i]);
          s[i]:=s[i]+x;
      i:=left[i];
          end;
    end;
  end;
splay(sum,0);
root:=sum;
end;
{-------------}
procedure find(x:longint);
var
i:int64;
begin
i:=root;
while true do
  begin
  if x<=size[left[i]] then i:=left[i]
  else if x=size[left[i]]+1 then
    begin
    splay(i,0);
    root:=i;
    exit;
    end
  else
    begin
    x:=x-size[left[i]]-1;
    i:=right[i];
    end;
  end;
end;
{-------------}
procedure ask;
begin
find(kk shr 1+1);
ans:=min(ans,size[left[root]]*a[root]-s[left[root]]+s[right[root]]-size[right[root]]*a[root]);
end;
{-------------}
procedure find_2(x:longint);
var
i:longint;
begin
i:=root;
while true do
  begin
  if x<a[i] then i:=left[i]
  else if x=a[i] then
    begin
    splay(i,0);
    root:=i;
    exit;
    end
  else
    i:=right[i];
  end;
end;
{-------------}
procedure delete(x:longint);
var
k2,k1,i:int64;
ii:longint;
begin
find_2(x);
i:=root;
k1:=left[i];
while (right[k1]<>0) and (k1<>0) do k1:=right[k1];
if k1<>0 then
splay(k1,root);
k2:=right[i];
while (left[k2]<>0) and (k2<>0) do k2:=left[k2];
if k2<>0 then
  splay(k2,root);
if k1<>0 then
  begin
  right[k1]:=right[root];
  fa[right[root]]:=k1;
  fa[k1]:=0;
  root:=k1;
  size[root]:=size[root]+size[right[root]];
  s[root]:=s[root]+s[right[root]];
  end
else
  begin
  left[k2]:=left[root];
  fa[left[root]]:=k2;
  fa[k2]:=0;
  root:=k2;
  size[root]:=size[root]+size[left[root]];
  s[root]:=s[root]+s[left[root]];
  end;
end;
{-------------}
begin
assign(input,'klo.in');
reset(input);
assign(output,'klo.out');
rewrite(output);
readln(m,kk);
if kk=1 then
  begin
  writeln(0);
  exit;
  end;
for i:=1 to kk do
  begin
  readln(p);
  a[i]:=p;
  insert(p);
  end;

ans:=maxlongint*100;
ask;
for i:=kk+1 to m do
  begin
  readln(p);
  delete(a[i-kk]);
  a[i]:=p;
  insert(p);
  ask;
  end;
writeln(ans);
close(output);
end.