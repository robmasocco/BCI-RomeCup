% ===== 3D plot =====
figure(1);

ax_sx = subplot(1,2,1);
title('Samples SX 3D');
hold on;
for i = 1:n_fft 
    if plotMode <= 0
        plot3(t, t_seq(1, ((i-1)*N+1):(i*N)), s_sx(i,:), 'Color', [0 0.4470 0.7410]);
    end
    if plotMode >= 0
        plot3(t, t_seq(1, ((i-1)*N+1):(i*N)), s_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
    end
end
if plotMode == 0
    legend("Segnale originale", "Segnale filtrato");
elseif plotMode <= -1
    legend("Segnale originale");
elseif plotMode >= 1
    legend("Segnale filtrato");
end
xlabel('Samples Time (s)');
ylabel('Time (s)');
zlabel('Magnitude');
view([0,-1,0]);
grid on;

ax_dx = subplot(1,2,2);
title('Samples DX 3D');
hold on;
for i = 1:n_fft 
    if plotMode <= 0
        plot3(t, t_seq(1, ((i-1)*N+1):(i*N)), s_dx(i,:), 'Color', [0 0.4470 0.7410]);
    end
    if plotMode >= 0
        plot3(t, t_seq(1, ((i-1)*N+1):(i*N)), s_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
    end
end
if plotMode == 0
    legend("Segnale originale", "Segnale filtrato");
elseif plotMode <= -1
    legend("Segnale originale");
elseif plotMode >= 1
    legend("Segnale filtrato");
end
xlabel('Samples Time (s)');
ylabel('Time (s)');
zlabel('Magnitude');
view([0,-1,0]);
grid on;

linkprop([ax_sx, ax_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});


% ===== 2D plot =====
if plotBlocks == 1
    pause;
    
    for i = 1:n_fft
        figure(2);

        ax_sx = subplot(1,2,1);
        title("Samples SX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        if plotMode <= 0
            plot(t, s_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotMode >= 0
            plot(t, s_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotMode == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotMode <= -1
            legend("Segnale originale");
        elseif plotMode >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Samples Time (s)');
        grid on;

        ax_dx = subplot(1,2,2);
        title("Samples DX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        if plotMode <= 0
            plot(t, s_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotMode >= 0
            plot(t, s_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotMode == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotMode <= -1
            legend("Segnale originale");
        elseif plotMode >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Samples Time (s)');
        grid on;

        linkaxes([ax_sx, ax_dx], 'x');

        pause;
        close;
    end
end