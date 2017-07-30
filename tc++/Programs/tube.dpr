
// Task  :  Winter Camp 2006 tube
// Time Complexity  :  O(MlogM + (N+Q)*logN)
// Memory Complexity  :  O(M + N + Q)
// It uses Link-Cut Tree to solve dynamic tree problem

program tube;

const
  maxn = 100000;
  maxm = 1000000;
  maxq = 100000;

type
  edge_type = record
    a, b, w : longint;
  end;

  po = ^edge_node;
  edge_node = record
    data, weight, no : longint;
    next : po;
  end;

  pointer = ^node;
  node = record
    value, maxv : array[0..1] of longint;
    rev, kind : boolean;
    ch : array[0..1] of pointer;
    pre : pointer;
  end;

var
  queue, s, rank : array[0..maxn] of longint;
  e, tmp : array[0..maxm] of edge_type;
  tree_e : array[0..maxn] of edge_type;
  op : array[0..maxq, 0..2] of longint;
  flag : array[0..maxm] of boolean;
  ans : array[0..maxq] of longint;
  loc : array[0..maxn] of pointer;
  v : array[0..maxn] of boolean;
  ge : array[0..maxn] of po;
  Null : pointer;

procedure Swap(var a, b : longint); overload;
  var
    t : longint;
  begin
    t := a;
    a := b;
    b := t;
  end;

procedure Swap(var a, b : edge_type); overload;
  var
    t : edge_type;
  begin
    t := a;
    a := b;
    b := t;
  end;

procedure Swap(var a, b : pointer); overload;
  var
    t : pointer;
  begin
    t := a;
    a := b;
    b := t;
  end;

procedure QSort1(head, tail : longint);
  var
    mid : edge_type;
    i, j : longint;
  begin
    i := head;
    j := tail;
    mid := e[(i + j) shr 1];
    repeat
      while (e[i].a < mid.a) or (e[i].a = mid.a) and (e[i].b < mid.b) do inc(i);
      while (e[j].a > mid.a) or (e[j].a = mid.a) and (e[j].b > mid.b) do dec(j);
      if i <= j then
        begin
          Swap(e[i], e[j]);
          inc(i);
          dec(j);
        end;
    until i > j;
    if head < j then QSort1(head, j);
    if i < tail then QSort1(i, tail);
  end;

procedure QSort2(head, tail : longint);
  var
    mid : edge_type;
    i, j : longint;
  begin
    i := head;
    j := tail;
    mid := tmp[(i + j) shr 1];
    repeat
      while tmp[i].w < mid.w do inc(i);
      while tmp[j].w > mid.w do dec(j);
      if i <= j then
        begin
          Swap(tmp[i], tmp[j]);
          inc(i);
          dec(j);
        end;
    until i > j;
    if head < j then QSort2(head, j);
    if i < tail then QSort2(i, tail);
  end;

function Binary_Search(a, b, tot : longint) : longint;
  var
    head, tail, mid : longint;
  begin
    head := 1;
    tail := tot;
    while head <= tail do
      begin
        mid := (head + tail) shr 1;
        if (a > e[mid].a) or (a = e[mid].a) and (b > e[mid].b) then
          head := mid + 1
        else
          tail := mid - 1;
      end;
    result := head;
  end;

function Find_Set(x : longint) : longint;
  var
    t, res, bak : longint;
  begin
    res := x;
    while s[res] <> res do res := s[res];
    t := x;
    while s[t] <> t do
      begin
        bak := s[t];
        s[t] := res;
        t := bak;
      end;
    result := res;
  end;

procedure Union(a, b : longint);
  begin
    a := Find_Set(a);
    b := Find_Set(b);
    if rank[a] < rank[b] then
      s[a] := b
    else
      begin
        s[b] := a;
        if rank[a] = rank[b] then inc(rank[a]);
      end;
  end;

procedure Update(x : pointer);
  var
    a, b, c : longint;
  begin
    if x = Null then exit;

    with x^ do
      begin
        a := ch[0]^.maxv[0];
        b := ch[1]^.maxv[0];
        c := value[0];
        if tree_e[a].w > tree_e[b].w then maxv[0] := a else maxv[0] := b;
        if tree_e[c].w > tree_e[maxv[0]].w then maxv[0] := c;

        a := ch[0]^.maxv[1];
        b := ch[1]^.maxv[1];
        c := value[1];
        if tree_e[a].w > tree_e[b].w then maxv[1] := a else maxv[1] := b;
        if tree_e[c].w > tree_e[maxv[1]].w then maxv[1] := c;
      end;
  end;

procedure Reverse(x : pointer);
  begin
    if x = Null then exit;
    x^.rev := not x^.rev;
    Swap(x^.ch[0], x^.ch[1]);
    Swap(x^.value[0], x^.value[1]);
    Swap(x^.maxv[0], x^.maxv[1]);
  end;

procedure Push_Down(x : pointer);
  begin
    if (x = Null) or (not x^.rev) then exit;
    Reverse(x^.ch[0]);
    Reverse(x^.ch[1]);
    x^.rev := false;
  end;

procedure Rotate(x : pointer; c : longint);
  var
    y : pointer;
  begin
    y := x^.pre;
    y^.ch[1-c] := x^.ch[c];
    if x^.ch[c] <> Null then x^.ch[c]^.pre := y;
    x^.pre := y^.pre;
    if y^.kind then
      if y = y^.pre^.ch[0] then
        y^.pre^.ch[0] := x
      else
        y^.pre^.ch[1] := x;
    y^.pre := x;
    x^.ch[c] := y;
    Update(y);
    Update(x);
    if not y^.kind then
      begin
        y^.kind := true;
        x^.kind := false;
      end;
  end;

procedure Splay(x : pointer);
  var
    y, z : pointer;
  begin
    Push_Down(x);
    while x^.kind do
      if not x^.pre^.kind then
        begin
          Push_Down(x^.pre);
          Push_Down(x);
          if x = x^.pre^.ch[0] then
            Rotate(x, 1)
          else
            Rotate(x, 0);
        end
      else
        begin
          y := x^.pre;
          z := y^.pre;
          Push_Down(z);
          Push_Down(y);
          Push_Down(x);
          if y = z^.ch[0] then
            if x = y^.ch[0] then
              begin
                Rotate(y, 1);
                Rotate(x, 1);
              end
            else
              begin
                Rotate(x, 0);
                Rotate(x, 1);
              end
          else
            if x = y^.ch[1] then
              begin
                Rotate(y, 0);
                Rotate(x, 0);
              end
            else
              begin
                Rotate(x, 1);
                Rotate(x, 0);
              end;
        end;
  end;

function Get_Top(x : pointer) : pointer;
  begin
    while true do
      begin
        Push_Down(x);
        if x^.ch[0] = Null then break;
        x := x^.ch[0];
      end;
    result := x;
  end;

procedure Expose(x : pointer);
  var
    u, v : pointer;
  begin
    u := x;
    v := Null;
    while u <> Null do
      begin
        Splay(u);
        u^.ch[1]^.kind := false;
        u^.ch[1] := v;
        u^.value[1] := Get_Top(v)^.value[0];
        Update(u);
        if v <> Null then v^.kind := true;
        v := u;
        u := u^.pre;
      end;
  end;

function Query_Max(a, b : longint) : longint;
  var
    u, v : pointer;
    res, x, y : longint;
  begin
    Expose(loc[a]);
    u := loc[b];
    v := Null;
    while u <> Null do
      begin
        Splay(u);
        if u^.pre = Null then
          begin
            x := u^.ch[1]^.maxv[0];
            y := v^.maxv[0];
            if tree_e[x].w > tree_e[y].w then
              res := x
            else
              res := y;
          end;
        u^.ch[1]^.kind := false;
        u^.ch[1] := v;
        u^.value[1] := Get_Top(v)^.value[0];
        Update(u);
        if v <> Null then v^.kind := true;
        v := u;
        u := u^.pre;
      end;
    result := res;
  end;

procedure Ins_Edge(a, b, w, c : longint);
  var
    p : po;
  begin
    new(p);
    p^.data := b;
    p^.weight := w;
    p^.no := c;
    p^.next := ge[a];
    ge[a] := p;
  end;

procedure Make_GE(n : longint);
  var
    i : longint;
  begin
    for i := 1 to n do ge[i] := nil;
    for i := 1 to n-1 do
      begin
        Ins_Edge(tree_e[i].a, tree_e[i].b, tree_e[i].w, i);
        Ins_Edge(tree_e[i].b, tree_e[i].a, tree_e[i].w, i);
      end;
  end;

function New_Node() : pointer;
  var
    p : pointer;
  begin
    new(p);
    with p^ do
      begin
        value[0] := 0;
        value[1] := 0;
        maxv[0] := 0;
        maxv[1] := 0;
        rev := false;
        kind := false;
        pre := Null;
        ch[0] := Null;
        ch[1] := Null;
      end;
    result := p;
  end;

procedure Make_Tree(n : longint);
  var
    i, head, tail : longint;
    p : po;
  begin
    Null := New_Node();
    Null^.pre := Null;
    Null^.ch[0] := Null;
    Null^.ch[1] := Null;
    for i := 1 to n do loc[i] := New_Node();

    fillchar(v, sizeof(v), false);
    v[1] := true;
    queue[1] := 1;
    head := 1;
    tail := 1;
    while head <= tail do
      begin
        p := ge[queue[head]];
        while p <> nil do
          begin
            if not v[p^.data] then
              begin
                loc[p^.data]^.pre := loc[queue[head]];
                loc[p^.data]^.value[0] := p^.no;
                v[p^.data] := true;
                inc(tail);
                queue[tail] := p^.data;
              end;
            p := p^.next;
          end;
        inc(head);
      end;
  end;

var
  n, m, q, i, j, a, b, tot, t : longint;
begin
  assign(input, 'tube.in');
  reset(input);
  readln(n, m, q);
  for i := 1 to m do
    begin
      readln(e[i].a, e[i].b, e[i].w);
      if e[i].a > e[i].b then Swap(e[i].a, e[i].b);
    end;
  QSort1(1, m);
  fillchar(flag, sizeof(flag), false);
  for i := 1 to q do
    begin
      read(op[i][0]);
      if op[i][0] = 1 then
        readln(op[i][1], op[i][2])
      else
        begin
          readln(a, b);
          if a > b then Swap(a, b);
          t := Binary_Search(a, b, m);
          flag[t] := true;
          op[i][1] := t;
        end;
    end;
  close(input);

  tot := 0;
  for i := 1 to m do
    if not flag[i] then
      begin
        inc(tot);
        tmp[tot] := e[i];
      end;
  QSort2(1, tot);
  for i := 1 to n do
    begin
      s[i] := i;
      rank[i] := 1;
    end;
  j := 1;
  for i := 1 to n-1 do
    begin
      while Find_Set(tmp[j].a) = Find_Set(tmp[j].b) do inc(j);
      Union(tmp[j].a, tmp[j].b);
      tree_e[i] := tmp[j];
    end;

  Make_GE(n);
  tree_e[0].w := 0;
  Make_Tree(n);
  for i := q downto 1 do
    if op[i][0] = 1 then
      ans[i] := tree_e[Query_Max(op[i][1], op[i][2])].w
    else
      begin
        t := Query_Max(e[op[i][1]].a, e[op[i][1]].b);
        if e[op[i][1]].w < tree_e[t].w then
          begin
            a := tree_e[t].a;
            b := tree_e[t].b;
            Splay(loc[a]);
            if loc[a]^.value[0] = t then Swap(a, b);
            Expose(loc[a]);
            Splay(loc[b]);
            loc[b]^.pre := Null;
            loc[b]^.value[0] := 0;
            Update(loc[b]);

            tree_e[t] := e[op[i][1]];
            a := tree_e[t].a;
            b := tree_e[t].b;
            Expose(loc[b]);
            Splay(loc[b]);
            Reverse(loc[b]);
            loc[b]^.pre := loc[a];
            loc[b]^.value[0] := t;
            Update(loc[b]);
          end;
      end;

  assign(output, 'tube.out');
  rewrite(output);
  for i := 1 to q do
    if op[i][0] = 1 then writeln(ans[i]);
  close(output);
end.
