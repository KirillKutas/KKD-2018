using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace GenerationCode
{
class Func
{
public int sum(int a1, int a2)
{
int q;
q = a1 + a2;
return q;
}

public int ppp(int a1, int a2)
{
int q;
q = a1 * a2;
return q;
}

public string asq()
{
string g;
g = Console.ReadLine();
return g;
}

}
class Program
{
static void Main(string[] args)

{
Lib lib = new Lib();
Func func = new Func();
string str;
str = Console.ReadLine();
Console.WriteLine(str);
int a = 6 / 8;
Console.WriteLine(a);
int f = 5 + lib.doub(2) + (7);
Console.WriteLine(f);
int b;
b = Int32.Parse(Console.ReadLine());
int c = a;
Console.WriteLine(c);
Console.WriteLine(lib.sqr(a));
int prim = func.sum(a, b);
Console.WriteLine(prim);
Console.WriteLine(func.ppp(a, b));
}

}
}
