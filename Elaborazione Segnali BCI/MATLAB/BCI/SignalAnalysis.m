s_sx = zeros(n_fft, N);
s_dx = zeros(n_fft, N);
s_f_sx = zeros(n_fft, N);
s_f_dx = zeros(n_fft, N);
for i = 1:n_fft
    s_sx(i,:) = signal_seq(1, ((i - 1) * N + 1) : (i*N));
    s_dx(i,:) = signal_seq(2, ((i - 1) * N + 1) : (i*N));
    s_f_sx(i,:) = signal_seq_filter(1, ((i - 1) * N + 1) : (i*N));
    s_f_dx(i,:) = signal_seq_filter(2, ((i - 1) * N + 1) : (i*N));
end
S_sx = monofft(s_sx, 2);
S_dx = monofft(s_dx, 2);
S_f_sx = monofft(s_f_sx, 2);
S_f_dx = monofft(s_f_dx, 2);