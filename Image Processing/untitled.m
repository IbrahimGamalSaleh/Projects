function varargout = untitled(varargin)
% UNTITLED MATLAB code for untitled.fig
%      UNTITLED, by itself, creates a new UNTITLED or raises the existing
%      singleton*.
%
%      H = UNTITLED returns the handle to a new UNTITLED or the handle to
%      the existing singleton*.
%
%      UNTITLED('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in UNTITLED.M with the given input arguments.
%
%      UNTITLED('Property','Value',...) creates a new UNTITLED or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before untitled_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to untitled_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help untitled

% Last Modified by GUIDE v2.5 23-Apr-2018 21:33:39

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before untitled is made visible.
function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to untitled (see VARARGIN)

% Choose default command line output for untitled
handles.output = hObject;

TabFontSize = 10;
TabNames = {'Image Histogram', 'Edge Detection'};
FigWidth = 0.265;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes untitled wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = untitled_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

global I;
global J;
global K;
global L;
global P;
global PBW;
global histP;
J=1;
K=1;
L=1;
% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global I;
global J;
global L;
global P;
global PBW;
global histP;
I=imgetfile;
P=imread(I);
PBW = rgb2gray(P);
histP = imhist(PBW);
axes(handles.axes1);
plot(histP);
axes(handles.axes5);
imshow(P);
J=0;
L=0;
%axesHandle = findobj('Tag', 'axes1');
%plot(axesHandle,[1 2 3],[1 2 3]);
%set(figure_handle,'CurrentAxes',axes1);
%imhist(PBW);


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global I;
global J;
global K;
global L;
global P;
global PBW;
global histP;
if J==0
    J=1;
elseif J==1 | L==0
    I=imgetfile;
    P=imread(I);
    PBW = rgb2gray(P);
    histP = imhist(PBW);
    axes(handles.axes1);
    plot(histP);
    L=0
end
K=0;
histE = imhist(histeq(P));
axes(handles.axes3);
plot(histE);
axes(handles.axes5);
imshow(histeq(P));


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global I;
global J;
global K;
global L;
global P;
global PBW;
global histP;
global histE;
if K==0
    histE = imhist(histeq(P));
    axes(handles.axes3);
    plot(histE);
    K=1;
elseif J==1
    I=imgetfile;
    P=imread(I);
    PBW = rgb2gray(P);
    histP = imhist(PBW);
    axes(handles.axes1);
    plot(histP);
    histE = imhist(histeq(P));
    axes(handles.axes3);
    plot(histE);
    L=0;
end
II=imgetfile;
PP=imread(II);
axes(handles.axes4);
plot(imhist(imhistmatch(P, PP)));
axes(handles.axes5);
imshow(imhistmatch(P, PP));


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global P;
global L;
global PBW;
if L==1
    I=imgetfile;
    P=imread(I);
end
L=1;
axes(handles.axes5);
imshow(P);
PBW=rgb2gray(P);
Edge = edge(PBW, 'sobel');
axes(handles.axes1);
imshow(Edge);
title('sobel');
Edge = edge(PBW, 'prewitt');
axes(handles.axes3);
imshow(Edge);
title('prewitt');
Edge = edge(PBW, 'canny');
axes(handles.axes4);
imshow(Edge);
title('canny');

% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over pushbutton4.
function pushbutton4_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
