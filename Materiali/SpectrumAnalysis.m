clc;
clear all;
close all;

Fs = 500;               % Frequenza campionamento               
T = 1/Fs;               % Periodo campionamento       
L = 500;                % Numero di campioni
t = (0:L-1)*T;          % vettore del tempo


%% Costruzione segnale
A = [1];
F = [11];
s = 0;
for k = 1:size(A,2)
    s = s + A(k)*sin(2*pi*F(k)*t);
end


%% Aggiunta disturbi
a = 0;                         % Ampiezza disturbo casuale
c = 0;                         % Ampiezza componente continua
x = s + c + a*randn(size(t));   % Calcolo segnale modificato


%% DFT
X = fft(x);                     % Trasformata Fourier segnale
S = fft(s);                     % Trasformata Fourier segnale originale
% Il vettore X è formato dalle frequenze:
% [0, 1/L, 2/L, ..., (L-1)/L, L/L = 1, -(L-1)/L, ..., -2/L, -1/L] * Fs/2
% La componente che vale Fs/2 va esclusa per il thm del campionamento in
% quanto si accettano segnali < a Fs/2 (non <=)


%% Calcolo dello spettro
P2x = abs(X)/L;                  % 2-sided spectrum. Si distringue tra frequenze positive e negative
P1x = P2x(1:L/2);                %    L'energia è divisa a metà tra le 2 frequenze opposte (eccezione f=0)
P1x(2:end-1) = 2*P1x(2:end-1);   % 1-sided spectrum. Unificazione delle frequenze opposte (f e -f) -> 2*energia di un lato

P2s = abs(S)/L;                  % 2-sided spectrum. Si distringue tra frequenze positive e negative
P1s = P2s(1:L/2);                %    L'energia è divisa a metà tra le 2 frequenze opposte (eccezione f=0)
P1s(2:end-1) = 2*P1s(2:end-1);   % 1-sided spectrum. Unificazione delle frequenze opposte (f e -f) -> 2*energia di un lato

f = Fs*(0:L/2-1)/L;              % vettore delle frequenze (-1 in quanto si esclude la frequenza Fs/2 per il thm del campionamento)


%% Plot
figure(1);
hold on;
plot(f, P1s);
plot(f, P1x);
legend('Segnale Originale', 'Segnale Campionato');
ylabel('Modulo');
xlabel('Frequenza (hz)');
grid on;