%S = 1
%I = 2
%R = 3

%Usage: [ts,ys] = ode45(@ode,[0 200],[0.985 0.015 0]);

function Fv=ode(t,Y);

%a = 0.000046*40000;
%b = 0.061295;
%c = 0.106566;
%d = 0.363213;
%e = 0.099968;

global a
global b
global c
global d
global e

Fv = zeros(3,1);

Fv(1,1) = -a*Y(1)*Y(2) + c*Y(2) + d*Y(2) + e*Y(3);
%Fv(2,1) = a*Y(1)*Y(2,1) - b*Y(2) - c*Y(2);
Fv(2,1) = a*Y(1)*Y(2) - b*Y(2) - c*Y(2) - d*Y(2);
Fv(3,1) = b*Y(2) - e*Y(3);