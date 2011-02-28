class ProjectsController < ApplicationController

  def nav
    'projects'
  end

  # GET /projects
  def index
    @projects = Project.all(:order => 'position')
  end

  # GET /projects/1
  def show
    if params[:id].to_i != 0
      @project = Project.find(params[:id])
    else
      @project = Project.find_by_name(params[:id].sub('_', ' '))
    end

    @title = ['Projects', @project.name]
  end


  #
  # Admin actions
  #
  
  require_user :new, :create, :destroy, :update, :edit, :move

  def move
    @project = Project.find(params[:id])
    m = @project.method('move_' + params[:direction])
    m.call()
    redirect_to projects_path
  end

  # GET /projects/new
  def new
    @project = Project.new
  end

  # GET /projects/1/edit
  def edit
    @project = Project.find(params[:id])
  end

  # POST /projects
  def create
    @project = Project.new(params[:project])

    if @project.save
      flash[:notice] = 'Project was successfully created.'
      redirect_to(@project)
    else
      render :action => "new"
    end
  end

  # PUT /projects/1
  def update
    @project = Project.find(params[:id])

    if @project.update_attributes(params[:project])
      flash[:notice] = 'Project was successfully updated.'
      redirect_to(@project)
    else
      render :action => "edit"
    end
  end

  # DELETE /projects/1
  def destroy
    @project = Project.find(params[:id])
    @project.destroy

    redirect_to(projects_url)
  end
end
