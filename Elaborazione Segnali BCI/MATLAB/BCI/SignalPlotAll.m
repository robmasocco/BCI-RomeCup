% ===== 3D plot =====
if plotGraphics <= 0
    fig = figure(5);
    
    ax_s_sx = subplot(2,2,1);
    title('Samples SX 3D');
    hold on;
    for i = start_fft:final_fft  
        times = ((i - 1) * step_N + 1) : ((i - 1) * step_N + N);
        if plotSignals <= 0
            plot3(t, t_seq(1, times), s_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(t, t_seq(1, times), s_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
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
    for i = start_fft:final_fft  
        times = ((i - 1) * step_N + 1) : ((i - 1) * step_N + N);
        if plotSignals <= 0
            plot3(t, t_seq(1, times), s_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(t, t_seq(1, times), s_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
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
    for i = start_fft:final_fft  
        time = ((i - 1) * step_t + sec) * ones(1, N/2);
        if plotSignals <= 0
            plot3(f, time, S_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(f, time, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
        legend("Segnale filtrato");
    end
    xlabel('Frequency (hz)');
    ylabel('Time (s)');
    zlabel('Magnitude');
    axis([f1 f2 start_fft*step_t final_fft*step_t 0 a]);
    view([0,-1,0]);
    grid on;

    ax_S_dx = subplot(2,2,4);
    title('Spectrum DX 3D');
    hold on;
    for i = start_fft:final_fft 
        time = ((i - 1) * step_t + sec) * ones(1, N/2);
        if plotSignals <= 0
            plot3(f, time, S_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(f, time, S_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
        legend("Segnale filtrato");
    end
    xlabel('Frequency (hz)');
    ylabel('Time (s)');
    zlabel('Magnitude');
    axis([f1 f2 start_fft*step_t final_fft*step_t 0 a]);
    view([0,-1,0]);
    grid on;

    Link1 = linkprop([ax_s_sx, ax_s_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
    setappdata(fig, 'Link1', Link1);
    Link2 = linkprop([ax_S_sx, ax_S_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
    setappdata(fig, 'Link1', Link2);
end



% ===== 2D plot =====
if plotGraphics >= 0
    pause;
    
    for i = start_fft:final_fft 
        figure(6);
        
        start_t = (i-1) * step_t;
        final_t = start_t + sec;
        ax_s_sx = subplot(2,2,1);
        title("Samples SX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
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
        title("Samples DX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
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
        title("Spectrum SX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
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
        title("Spectrum DX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
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