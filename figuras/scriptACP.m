SIZE=400;
TAM=SIZE*SIZE;
ITER = 100;
global a
global b
global c
global d
global e

SIM=1
PC=06
PD=03
PN=01
K=1
PercIni=0005

nome=sprintf('..\\resultados\\SIRD_SIM_01_PC_0000_PD_0000_PN_0000_K_0145_PercIni_0000.csv');

A=dlmread(nome, ';', [1 0 ITER 11]); %linha inicial - coluna inicial - linha final - coluna final

s=A(:,1); %coluna de s
i=A(:,2); %coluna de i
r=A(:,3); %coluna de r

plot(s,'k-','LineWidth',5);
hold
plot(i,'k:','LineWidth',5);
plot(r,'k--','LineWidth',5);

%ODE - Não esquecer de multiplicar por nxn = N^2
a = mean(A(ITER-20+1:ITER,8))*TAM;
b = mean(A(ITER-20+1:ITER,9));
c = mean(A(ITER-20+1:ITER,10));
d = 0;
e = mean(A(ITER-20+1:ITER,11));

set(gca,'XLim',[0 ITER])
set(gca,'XTick',[0:50:ITER])
set(gca,'YLim',[0 TAM])
set(gca,'YTick',[0:TAM/4:TAM])
set(gca,'YTickLabels',[0:.25:1])
set(gcf,'color','white')
colormap(gray);
hFig = figure(1);
xlabel('time steps','FontSize',30,'Color','k');
ylabel({'normalized concentrations';'of individuals'},'FontSize',30);
set(gca,'FontSize',30)


set(gcf, 'Windowstyle', 'normal'); % usar se a linha de baixo der erro de WindowStyle docked
set(hFig, 'Position', [60 60 1400 800]);

legend('S(t)_{PCA}','I(t)_{PCA}','R(t)_{PCA}')

s=sprintf('..\\resultados\\ACP__SIM_%02d_PC_%02d_PD_%02d_PN_%02d_K_%02d_PercIni_%04d.fig', SIM, PC, PD, PN, K, PercIni);
saveas(gcf,s)

s=sprintf('..\\resultados\\ACP__SIM_%02d_PC_%02d_PD_%02d_PN_%02d_K_%02d_PercIni_%04d.eps', SIM, PC, PD, PN, K, PercIni);
saveas(gcf,s)

s=sprintf('..\\resultados\\ACP__SIM_%02d_PC_%02d_PD_%02d_PN_%02d_K_%02d_PercIni_%04d.png', SIM, PC, PD, PN, K, PercIni);
saveas(gcf,s)

close(gcf);