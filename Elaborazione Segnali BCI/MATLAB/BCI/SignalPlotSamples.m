% ===== 3D plot =====
if plotGraphics <= 0
    figure(1);
    
    ax_sx = subplot(1,2,1);
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

    ax_dx = subplot(1,2,2);
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

    linkprop([ax_sx, ax_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
end


% ===== 2D plot =====
if plotGraphics >= 0
    pause;
    
    for i = start_fft:final_fft 
        figure(2);
        
        start_t = (i-1) * step_t;
        final_t = start_t + sec;
        ax_sx = subplot(1,2,1);
        title("Samples SX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
        hold on;
        if plotSignals <= 0
            plot(t, s_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot(t, s_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotSignals == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotSignals <= -1
            legend("Segnale originale");
        elseif plotSignals >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Samples Time (s)');
        grid on;

        ax_dx = subplot(1,2,2);
        title("Samples DX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
        hold on;
        if plotSignals <= 0
            plot(t, s_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot(t, s_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotSignals == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotSignals <= -1
            legend("Segnale originale");
        elseif plotSignals >= 1
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