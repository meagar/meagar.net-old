class DesignsController < ApplicationController

  def initialize
		super
    @title = ["Web Designs"]
  end

  def nav
    'designs'
  end

  # GET /designs
  def index
    @designs = Design.all(:order => 'position')
  end

  # GET /designs/1
  def show
    @design = Design.find(params[:id])
    @title << @design.title
  end

  #
  # Admin actions
  #

  require_user :new, :create, :destroy, :edit, :update, :move

  def move
    @design = Design.find(params[:id])
    m = @design.method('move_' + params[:direction])
    m.call()
    redirect_to :action => :index
  end

  # GET /designs/new
  def new
    @design = Design.new
  end

  # GET /designs/1/edit
  def edit
    @design = Design.find(params[:id])
  end

  # POST /designs
  def create
    @design = Design.new(params[:design])

    if @design.save
      flash[:notice] = 'Design was successfully created.'
      redirect_to(@design)
    else
      render :action => "new"
    end
  end

  # PUT /designs/1
  def update
    @design = Design.find(params[:id])

    if @design.update_attributes(params[:design])
      flash[:notice] = 'Design was successfully updated.'
      redirect_to(@design)
    else
      render :action => "edit"
    end
  end

  # DELETE /designs/1
  def destroy
    @design = Design.find(params[:id])
    @design.destroy

    redirect_to(designs_url)
  end

end
