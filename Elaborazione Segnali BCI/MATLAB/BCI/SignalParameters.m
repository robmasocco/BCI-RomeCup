FS = 4000;                          % Frequenza di campionamento del segnale
TS = 1/FS;                          % Tempo di campionamento
sec = 2;                            % Secondi considerati per la fft
step_sec = 0.25;                    % Secondi di avanzamento del finestra temporale considerata per la fft          

freq1 = 2 * pi * 1;                 % Frequenza angolare di azione iniziale del filtro di Butterworth
freq2 = 2 * pi * 50;                % Frequenza angolare di azione finale del filtro di Butterworth
freq = [freq1, freq2];              % frequenze angolari di azione del filtro
deg = 2;                            % grado del filtro di Butterworth
type = "band";                      % Tipo filtro

N = FS * sec;                       % Numero campioni per fft
f_bin = 1 / sec;                    % Ampiezza frequency bin della fft
f = f_bin * (0:N/2-1);              % Lista delle frequenza

len = size(signal_seq, 2);          % Numero campioni del segnale 
step_N = floor(step_sec/TS);        % Step in campioni per la fft successiva
step_t = step_N * TS;               % Step in tempo per la fft successiva
n_fft = floor((len-N)/step_N)+1;    % Numero di fft 
t = TS * (0:N-1);                   % Lista dei tempi dei campioni di un blocco
t_seq = TS * (0:len-1);             % Lista dei tempi della sequenza di campioni

plotSignals = -1;                   % [0 = o+f, -1 = o, 1 = f] Indica quali segnali inserire nei plot (o = originale, f = filtrato)
plotGraphics = 1;                   % [0 = 3D+2D, -1 = 3D, 1 = 2D] Indica se fare i plot 3D o 2D
start_time = 0;                     % Tempo iniziale visualizzato nei plot
final_time = 60;                    % Tempo finale visualizzato nei plot
f1 = 5;                             % Frequenza iniziale visualizzata dei plot degli spettri
f2 = 45;                            % Frequenza finale visualizzata dei plot degli spettri
a = 100;                            % Ampiezza visualizzata nei plot degli spettri

start_fft = max(1, floor(start_time / step_t) + 1);
final_fft = min(n_fft, floor((final_time - sec) / step_t) + 1);