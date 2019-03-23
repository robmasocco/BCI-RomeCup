% ===== 3D plot =====
figure(1);

ax_sx = subplot(1,2,1);
title('Samples SX 3D');
hold on;
for i = 1:n_fft 
    plot3(t, sec * i * ones(1, N), s_sx(i,:), 'Color', [0 0.4470 0.7410]);
    if plotFilter == 1
        plot3(t, sec * i * ones(1, N), s_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
    end
end
if plotFilter == 1
    legend("Segnale originale", "Segnale Filtrato");
end
xlabel('Samples Time (s)');
ylabel('Time (s)');
zlabel('Magnitude');
view([0,-1,0]);
grid on;

ax_dx = subplot(1,2,2);
title('Spectrum DX 3D');
hold on;
for i = 1:n_fft 
    plot3(t, sec * i * ones(1, N), s_dx(i,:), 'Color', [0 0.4470 0.7410]);
    if plotFilter == 1
        plot3(t, sec * i * ones(1, N), s_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
    end
end
if plotFilter == 1
    legend("Segnale originale", "Segnale Filtrato");
end
xlabel('Samples Time (s)');
ylabel('Time (s)');
zlabel('Magnitude');
view([0,-1,0]);
grid on;

Link = linkprop([ax_sx, ax_dx],{'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
setappdata(gcf, 'StoreTheLink', Link);

pause;

if plotBlocks == 1
    for i = 1:n_fft
        figure(3);

        ax_sx = subplot(1,2,1);
        title("Samples SX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        plot(t, s_sx(i,:));
        if plotFilter == 1
            plot(t, s_f_sx(i,:));
            legend("Segnale originale", "Segnale Filtrato");
        end
        ylabel('Magnitude');
        xlabel('Samples Time (s)');
        grid on;

        ax_dx = subplot(1,2,2);
        title("Samples DX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        plot(t, s_dx(i,:));
        if plotFilter == 1
            plot(t, s_f_dx(i,:));
            legend("Segnale originale", "Segnale Filtrato");
        end
        ylabel('Magnitude');
        xlabel('Samples Time (s)');
        grid on;

        linkaxes([ax_sx, ax_dx], 'xy');

        pause;
        close;
    end
end