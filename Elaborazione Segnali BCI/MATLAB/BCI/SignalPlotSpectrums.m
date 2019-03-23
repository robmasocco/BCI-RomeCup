% ===== 3D plot =====
figure(2);

ax_sx = subplot(1,2,1);
title('Spectrum SX 3D');
hold on;
for i = 1:n_fft 
    plot3(f, sec * i * ones(1, N/2), S_sx(i,:), 'Color', [0 0.4470 0.7410]);
    if plotFilter == 1
        plot3(f, sec * i * ones(1, N/2), S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
    end
end
if plotFilter == 1
    legend("Segnale originale", "Segnale Filtrato");
end
xlabel('Frequency (hz)');
ylabel('Time (s)');
zlabel('Magnitude');
axis([5 45 0 n_fft*sec 0 a]);
view([0,-1,0]);
grid on;

ax_dx = subplot(1,2,2);
title('Spectrum DX 3D');
hold on;
for i = 1:n_fft 
    plot3(f, sec * i * ones(1, N/2), S_dx(i,:), 'Color', [0 0.4470 0.7410]);
    if plotFilter == 1
        plot3(f, sec * i * ones(1, N/2), S_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
    end
end
if plotFilter == 1
    legend("Segnale originale", "Segnale Filtrato");
end
xlabel('Frequency (hz)');
ylabel('Time (s)');
zlabel('Magnitude');
axis([f1 f2 0 n_fft*sec 0 a]);
view([0,-1,0]);
grid on;

Link = linkprop([ax_sx, ax_dx],{'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
setappdata(gcf, 'StoreTheLink', Link);

pause;

if plotBlocks == 1
    for i = 1:n_fft
        figure(4);

        ax_sx = subplot(1,2,1);
        title("Spectrum SX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        plot(f, S_sx(i,:));
        if plotFilter == 1
            plot(f, S_f_sx(i,:));
            legend("Segnale originale", "Segnale Filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequency (hz)');
        axis([f1 f2 0 a]);
        grid on;

        ax_dx = subplot(1,2,2);
        title("Spectrum DX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        plot(f, S_dx(i,:));
        if plotFilter == 1
            plot(f, S_f_sx(i,:));
            legend("Segnale originale", "Segnale Filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequency (hz)');
        axis([f1 f2 0 a]);
        grid on;

        linkaxes([ax_sx, ax_dx], 'xy');

        pause;
        close;
    end
end