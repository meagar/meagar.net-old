class ProjectFilesController < ApplicationController
  
  #caches_page :show

  def nav
    'projects'
  end

  # GET /files/1
  def show
    @file = Project_file.find(params[:id])
    @title = [@file.project.name, @file.filename]

    if @file.content_type =~ /^image*/
      render :action => 'show_image'
    elsif @file.content_type =~ /^source*/ or @file.content_type =~ /^text*/
      render :action => 'show_source'
    elsif @file.content_type =~ /^application*/
      redirect_to :action => 'save', :id => @file
    end
  end

  # GET /files/save/1
  def save
    @file = Project_file.find(params[:id])
    send_file("public/#{@file.url}", :filename => @file.filename, :type => @file.mime_type)
  end

  #
  # Admin actions
  #

  require_user :new, :create, :destroy, :edit, :update, :move
 
  def move
    @file = Project_file.find(params[:id])
    m = @file.method('move_' + params[:direction])
    m.call()
    redirect_to @file.project
  end

  # GET /files/new
  def new
    @file = Project_file.new
    @project = Project.find(params[:project_id])
  end

  # GET /files/1/edit
  def edit
    @file = Project_file.find(params[:id])
  end

  def update
    @file = Project_file.find(params[:id])
    if @file.update_attributes(params[:project_file])
      expire(@file)
      flash[:notice] = 'Project_file was successfully updated'
      redirect_to (@file.project)
    else
      render :action => 'edit'
    end
  end

  # POST /files
  def create
    @file = Project_file.new params[:project_file]
    @project = Project.find(params[:project_id])
    @file.project_id = @project.id

    if @file.save
      flash[:notice] = 'Project_file was successfully created.'
      redirect_to project_url(@project)
    else
      render :action => "new"
    end
  end

  # DELETE /files/1
  def destroy
    @file = Project_file.find(params[:id])
    @project = @file.project
    if @file
      expire(@file)
      @file.destroy
      redirect_to @project
    end
  end

  private

  def expire(file)
    # doesn't seem to play well with nested routes, using 
    # expire_page(:controller => 'file', :action => 'show', :id => ...)
    # tries to delete /files/show/id.htm instead of
    # /projects/project_id/files/file_id
    expire_page("/projects/#{@file.project_id}/files/#{@file.id}.html");
  end

end
