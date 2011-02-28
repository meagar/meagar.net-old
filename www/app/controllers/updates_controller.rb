class UpdatesController < ApplicationController

  # GET /updates
  def index
    @updates = Update.all(:order => 'created_at DESC')
  end

  # GET /updates/1
  def show
    @update = Update.find(params[:id])
  end

  #
  # Admin actions
  #
  
  require_user :new, :create, :destroy, :edit, :update

  # GET /updates/new
  def new
    @update = Update.new
  end

  # GET /updates/1/edit
  def edit
    @update = Update.find(params[:id])
  end

  # POST /updates
  def create
    @update = Update.new(params[:update])

    if @update.save
      flash[:notice] = 'Update was successfully created.'
      redirect_to(@update)
    else
      render :action => "new"
    end
  end

  # PUT /updates/1
  def update
    @update = Update.find(params[:id])

    if @update.update_attributes(params[:update])
      flash[:notice] = 'Update was successfully updated.'
      redirect_to(@update)
    else
      render :action => "edit"
    end
  end

  # DELETE /updates/1
  def destroy
    @update = Update.find(params[:id])
    @update.destroy

    redirect_to(updates_url)
  end
end
