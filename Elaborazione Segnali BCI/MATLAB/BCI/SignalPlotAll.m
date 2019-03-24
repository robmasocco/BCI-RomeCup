% ===== 3D plot =====
fig = figure(5);

ax_s_sx = subplot(2,2,1);
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

ax_s_dx = subplot(2,2,2);
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


ax_S_sx = subplot(2,2,3);
title('Spectrum SX 3D');
hold on;
for i = 1:n_fft 
    if plotMode <= 0
        plot3(f, sec * i * ones(1, N/2), S_sx(i,:), 'Color', [0 0.4470 0.7410]);
    end
    if plotMode >= 0
        plot3(f, sec * i * ones(1, N/2), S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
    end
end
if plotMode == 0
    legend("Segnale originale", "Segnale filtrato");
elseif plotMode <= -1
    legend("Segnale originale");
elseif plotMode >= 1
    legend("Segnale filtrato");
end
xlabel('Frequency (hz)');
ylabel('Time (s)');
zlabel('Magnitude');
axis([5 45 0 n_fft*sec 0 a]);
view([0,-1,0]);
grid on;

ax_S_dx = subplot(2,2,4);
title('Spectrum DX 3D');
hold on;
for i = 1:n_fft 
    if plotMode <= 0
        plot3(f, sec * i * ones(1, N/2), S_dx(i,:), 'Color', [0 0.4470 0.7410]);
    end
    if plotMode >= 0
        plot3(f, sec * i * ones(1, N/2), S_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
    end
end
if plotMode == 0
    legend("Segnale originale", "Segnale filtrato");
elseif plotMode <= -1
    legend("Segnale originale");
elseif plotMode >= 1
    legend("Segnale filtrato");
end
xlabel('Frequency (hz)');
ylabel('Time (s)');
zlabel('Magnitude');
axis([f1 f2 0 n_fft*sec 0 a]);
view([0,-1,0]);
grid on;

Link1 = linkprop([ax_s_sx, ax_s_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
setappdata(fig, 'Link1', Link1);
Link2 = linkprop([ax_S_sx, ax_S_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
setappdata(fig, 'Link1', Link2);

% ===== 2D plot =====
if plotBlocks == 1
    pause;
    
    for i = 1:n_fft
        figure(6);

        ax_s_sx = subplot(2,2,1);
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

        ax_s_dx = subplot(2,2,2);
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

        linkaxes([ax_s_sx, ax_s_dx], 'x');
        
        
        ax_S_sx = subplot(2,2,3);
        title("Spectrum SX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        if plotMode <= 0
            plot(f, S_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotMode >= 0
            plot(f, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotMode == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotMode <= -1
            legend("Segnale originale");
        elseif plotMode >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequenxy (hz)');
        axis([f1 f2 0 a]);
        grid on;

        ax_S_dx = subplot(2,2,4);
        title("Spectrum DX in [" + num2str((i-1) * sec) + " , " + num2str(i * sec) + "] s");
        hold on;
        if plotMode <= 0
            plot(f, S_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotMode >= 0
            plot(f, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotMode == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotMode <= -1
            legend("Segnale originale");
        elseif plotMode >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequenxy (hz)');
        axis([f1 f2 0 a]);
        grid on;

        linkaxes([ax_S_sx, ax_S_dx], 'x');
        
        
        pause;
        close;
    end
end