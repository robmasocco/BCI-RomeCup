[num, den] = butterworth(deg, freq, type);
filter_s = tf(num, den);
filter_z = c2d(filter_s, TS, 'zoh');

signal_seq_filter = filterSignal(filter_z, signal_seq, TS, 2);
signal_seq_filter_sx = signal_seq_filter(1,:);
signal_seq_filter_dx = signal_seq_filter(2,:);