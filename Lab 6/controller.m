%% controller.m
% This code was created for ME 451 Lab 6, remote version
% A simulation of a motor controller with bang-bang or PID that students
% will tune and play with to understand the behavior of these controllers.

%% Simulation settings
%%%%% You should modify the settings and parameters as per the doc %%%%%
% bang_bang: this variable is how we are setting (in this lab only!)
% whether we are using the bang-bang or PID controller in our simulation.
%   true:   bang-bang controller
%   false:  PID controller
bang_bang = true;
% step_input: this variable determines whether the the setpoint in our
% simulation is the classic "step input" (setpoint goes instantly to 1).
%   true:   step input for setpoint
%   false:  sine wave input for setpoint
step_input = true;
% external_bias: this variable determines whether there is an external
% force that is pushing the system down (e.g gravity, or a load).
external_bias = false;

%% Animation settings
%%%%% You can change this if you want, up to you %%%%%
% animating: set to true to watch an animation, set to false to just plot
animating = false;
% animate_speed: speed multiplier for the animation, 1 = real-time
animate_speed = 1;

%% Motor parameters
%%%%% You should not modify these lines of code %%%%%
% Based off of a real motor + gearbox example. Units are kg, cm, rad, s.
% V: the supply voltage at which the motor's characteristics are evaluated
V = 12;
% t_stall: the stall torque of the motor at V
t_stall = 14;
% i_stall: the stall current of the motor at V
i_stall = 5.6;
% w_noload: the no-load speed of the motor at V, in rad/s
w_nl = 330 * 2 * pi / 60;
% i_noload: the no-load current of the motor at V
i_nl = 0.2;
% R: the motor's electrical resistance
R = V / i_stall;
% k: the motor constant. See https://en.wikipedia.org/wiki/Motor_constants
%   Tells us the resulting torque from a certain amount of current
%   Also tells us the resulting back-EMF from a certain motor velocity
% Calculating the motor constant in different ways may yield slightly
% different results.
k = i_stall / t_stall;
% F_k: the motor's kinetic friction and internal air resistance, simplified
F_k = i_nl / k;
% I: the motor and gearbox's combined rotational inertia, estimated
I = .1;

%% Bang-bang parameters
%%%%% You should modify the settings and parameters as per the doc %%%%%
% These parameters affect the behavior of the bang-bang controller.
% You will modify these as part of the lab
supply_voltage = 1;

%% PID parameters
% These parameters affect the behavior of the PID controller.
% You will modify these as part of the lab
Kp = 1;
Ki = 0;
Kd = 0;

%% Simulation
%%%%% You should not modify the simulation or these lines of code %%%%%

% Run the simulation
% The way we have set up our particular simulation takes the values we have
% set up above into account. If you are ever making your own simulation or
% controller, you will be able to pick how you set variables yourself.

% data contains:
%   data.setpoint: where the system was attempting to go
%   data.response: the simulated resulting position for the system
tic
data = sim('controller_sim');
disp(['Simulation computation time: ' num2str(toc) ' seconds'])

% Extract raw data from timeseries structures
time = data.setpoint.Time;
setpoint = data.setpoint.Data;
response = data.response.Data;

%% Plotting
%%%%% You can leave these lines alone or modify them if you want %%%%%
% If the figure doesn't exist, make it
if ~ishandle(1001)
    figure(1001);
    set(gcf, 'Units', 'inches');
    pos = get(gcf, 'Position');
    set(gcf, 'Position', [pos(1), pos(2), 6.5, 4]);
end

% Set and clear the figure
figure(1001); clf;

%%%%% You should modify the labels, especially the title, to fit %%%%%
hold on; grid on;
% Label the graph appropriately
ylabel('Position (unitless)')
xlabel('Time (s)')
title('... Controller Response to ...')

if animating
    % Create plot handles based on the first datapoint
    line_setpoint = plot(time(1), setpoint(1), '--', 'Color', [0 127/255 255/255], 'LineWidth', 2);
    line_response = plot(time(1), response(1), 'k', 'LineWidth', 2);
    % Plot additional lines and legend as suitable for the type of simulation
    if step_input == true
        legend('Setpoint', 'Response', 'Location', 'Southeast')
    else
        % The sine wave input has upper and lower bounds to stay within
        line_upper = plot(time(1), setpoint(1) + .1, ':', 'Color', [0 127/255 255/255], 'LineWidth', 1.5);
        line_lower = plot(time(1), setpoint(1) - .1, ':', 'Color', [0 127/255 255/255], 'LineWidth', 1.5);
        legend('Setpoint', 'Response', 'Outer Bounds', 'Location', 'Southwest')
    end
    % Draw the figure as-is
    drawnow
    
    % Animate frame-by-frame, doing its best to follow at the set pace.
    % Setting animate_speed too high may lead to inconsistent animation.
    % Start the timer
    tic()
    for i = 2:length(time)
        % If we're moving too slow, skip frames
        if (toc() > time(i) / animate_speed)
            continue
        end
        
        % Otherwise, we update the plot
        % Update the line data
        line_setpoint.XData = time(1:i);
        line_setpoint.YData = setpoint(1:i);
        line_response.XData = time(1:i);
        line_response.YData = response(1:i);
        
        if step_input == true
            % Set reasonable axis limits
            xlim([0, min([time(end); time(i) * 1.1])])
            ylim([0, max([1.1; response(1:i) * 1.1])])
        else
            
            % More lines to update for a mobile setpoint
            line_upper.XData = time(1:i);
            line_upper.YData = setpoint(1:i) + .1;
            line_lower.XData = time(1:i);
            line_lower.YData = setpoint(1:i) - .1;
            % Set reasonable axis limits
            
            xlim([0, min([time(end); time(i) * 1.1])])
            ylim([-1.2, 1.2])
        end
        
        % Refresh the plot
        drawnow
        
        % Until enough time has passed, wait
        while (toc < time(i - 1) / animate_speed)
            pause(0.0001)
        end
    end
else
    % Plot core data (setpoint and response)
    plot(time, setpoint, '--', 'Color', [0 127/255 255/255], 'LineWidth', 2)
    plot(time, response, 'k', 'LineWidth', 2)
    % Plot additional lines and legend as suitable for the type of simulation
    if step_input == true
        legend('Setpoint', 'Response', 'Location', 'Southeast')
    else
        % The sine wave input has upper and lower bounds to stay within
        plot(time, setpoint + .1, ':', 'Color', [0 127/255 255/255], 'LineWidth', 1.5)
        plot(time, setpoint - .1, ':', 'Color', [0 127/255 255/255], 'LineWidth', 1.5)
        legend('Setpoint', 'Response', 'Upper Bound', 'Lower Bound', 'Location', 'Southeast')
    end
end

% LaTeX can directly import vector images that do not suffer the resolution
% issues that pixel-based image formats like JPEG and PNGs do.
% Overleaf uses pdfLaTeX by default, so we will store our images in PDFs,
% but usually it is done in EPS files.

% This set of code stores our figure in an appropriately-sized PDF file:
fig_size = get(gcf, 'Position');
axes_title = get(gca, 'Title');
set(gcf,...
    'PaperPosition',[0 0 fig_size(3:4)],...
    'PaperSize', fig_size(3:4));
print('-dpng', '-r300', [axes_title.String '.png']);
print('-dpdf', [axes_title.String '.pdf']);
