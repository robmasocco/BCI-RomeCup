signal = importdata('-pastespecial');

N_B = size(signal, 1);    % numero di blocchi di campioni
N_S = size(signal, 2);    % numero di campioni per blocco

signal_sx = zeros(N_B/2, N_S);
signal_dx = zeros(N_B/2, N_S);

signal_seq_sx = zeros(1, N_B/2 * N_S);
signal_seq_dx = zeros(1, N_B/2 * N_S);

signal_seq = zeros(2, N_B/2 * N_S);

for i = 1:(N_B/2)
   signal_sx(i,:) = signal(2*i - 1,:); 
   signal_dx(i,:) = signal(2*i    ,:);
   
   signal_seq_sx(1, ((i-1) * N_S + 1):(i*N_S) ) = signal_sx(i,:);
   signal_seq_dx(1, ((i-1) * N_S + 1):(i*N_S) ) = signal_dx(i,:);
end

signal_seq(1,:) = signal_seq_sx(1,:);
signal_seq(2,:) = signal_seq_dx(1,:);