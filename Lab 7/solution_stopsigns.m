% image_path = 'Lab 7 Images/test1.png';
image_raw = imread('test1.png');

cascade_classify = true;
rcnn_classify = true;

%% Cascade Classifier
% Check if the cascade classifier has been trained
already_trained = false;

d = dir;
for i = 1:length(dir)
    already_trained = already_trained || strcmp(d(i).name, 'stopSignDetector.xml');
end

% If not, train it
if ~already_trained
    load('stopSignsAndCars.mat');
    positiveInstances = stopSignsAndCars(:, 1:2);
    imDir = fullfile(matlabroot, 'toolbox', 'vision', 'visiondata', ...
        'stopSignImages');
    addpath(imDir);
    negativeFolder = fullfile(matlabroot, 'toolbox', 'vision', 'visiondata', ...
        'nonStopSigns');
    negativeImages = imageDatastore(negativeFolder);
    trainCascadeObjectDetector('stopSignDetector.xml', positiveInstances, ...
        negativeFolder, 'FalseAlarmRate', 0.1, 'NumCascadeStages', 5);
end

if cascade_classify
    detector = vision.CascadeObjectDetector('stopSignDetector.xml');
    bbox = detector(image_raw);
    
    cascade_image = insertObjectAnnotation(image_raw, 'rectangle', bbox, 'stop sign');
    figure; imshow(cascade_image);
end

%% R-CNN Classifier
% Check if the RCNN has been trained
if ~exist('rcnn', 'var')
    load('rcnnStopSigns.mat', 'stopSigns', 'layers')
    imDir = fullfile(matlabroot, 'toolbox', 'vision', 'visiondata',...
        'stopSignImages');
    addpath(imDir);
    options = trainingOptions('sgdm', ...
        'MiniBatchSize', 32, ...
        'InitialLearnRate', 1e-6, ...
        'MaxEpochs', 10);
    rcnn = trainRCNNObjectDetector(stopSigns, layers, options, 'NegativeOverlapRange', [0 0.3]);
end

if rcnn_classify
    [bbox, score, label] = detect(rcnn, image_raw, 'MiniBatchSize', 32);
    rcnn_image = image_raw;
    for i = 1:length(label)
        annotation = sprintf('%s: (Confidence = %f)', label(i), score(i));
        rcnn_image = insertObjectAnnotation(rcnn_image, 'rectangle', bbox(i, :), annotation);
    end
    figure; imshow(rcnn_image);
end