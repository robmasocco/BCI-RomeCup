FS = 4000;                  % Frequenza di campionamento del segnale
TS = 1/FS;                  % Tempo di campionamento
sec = 60;                    % Secondi considerati per la fft

freq1 = 2 * pi * 1;         % Frequenza angolare di azione iniziale del filtro di Butterworth
freq2 = 2 * pi * 50;        % Frequenza angolare di azione finale del filtro di Butterworth
freq = [freq1, freq2];      % frequenze angolari di azione del filtro
deg = 2;                    % grado del filtro di Butterworth
type = "band";              % Tipo filtro

N = FS * sec;               % Numero campioni per fft
f_bin = 1 / sec;            % Ampiezza frequency bin della fft
f = f_bin * (0:N/2-1);      % Lista delle frequenza

len = size(signal_seq, 2);  % Numero campioni del segnale 
n_fft = floor(len / N);     % Numero di fft 
t = TS * (0:N-1);           % Lista dei tempi dei campioni di un blocco
t_seq = TS * (0:len-1);     % Lista dei tempi della sequenza di campioni

plotFilter = 0;             % [1 = si, 0 = no] Indica se inserire nei plot il segnale filtrato
plotBlocks = 1;             % [1 = si, 0 = no] Indica se fare il plot 2D blocco per blocco
f1 = 0;                     % Frequenza iniziale visualizzata dei plot degli spettri
f2 = 60;                    % Frequenza finale visualizzata dei plot degli spettri
a = 500;                    % Ampiezza visualizzata nei plot degli spettri