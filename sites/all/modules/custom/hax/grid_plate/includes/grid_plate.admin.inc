<?php

/**
 * @file
 * grid_plate editing UI.
 */

/**
 * UI controller.
 */
class GridPlateUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();

    // Change the overview menu type for the list of Grid Plate.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'Grid Plate';

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items['grid_plate/' . $wildcard] = array(
      'title callback' => 'grid_plate_page_title',
      'title arguments' => array(1),
      'page callback' => 'grid_plate_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Grid Plate.
 */
function grid_plate_form($form, &$form_state, $grid_plate, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  grid_plate_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Grid Plate Label'),
    '#default_value' => isset($grid_plate->label) ? $grid_plate->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['grid_plate'] = $grid_plate;
  field_attach_form('grid_plate', $grid_plate, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Grid Plate'),
    '#submit' => $submit + array('grid_plate_edit_form_submit'),
  );

  if (!empty($grid_plate->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Grid Plate'),
      '#suffix' => l(t('Cancel'), 'admin/content/grid_plate'),
      '#submit' => $submit + array('grid_plate_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('grid_plate_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Grid Plate form.
 */
function grid_plate_edit_form_validate(&$form, &$form_state) {
  $grid_plate = $form_state['grid_plate'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('grid_plate', $grid_plate, $form, $form_state);
}

/**
 * Form API submit callback for the Grid Plate form.
 */
function grid_plate_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Grid Plate.
  $grid_plate = entity_ui_controller('grid_plate')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $grid_plate->is_new = isset($grid_plate->is_new) ? $grid_plate->is_new : 0;
  if ($is_new_entity) {
    $grid_plate->created = time();
  }

  $grid_plate->changed = time();

  $grid_plate->save();

  // Send feedback message to the user.
  $message = t("Grid Plate :label updated.", array(':label' => $grid_plate->label));

  if ($is_new_entity) {
    $message = t("Grid Plate :label created.", array(':label' => $grid_plate->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/grid_plate';
}

/**
 * Form API submit callback for the delete button.
 */
function grid_plate_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/grid_plate/manage/' . $form_state['grid_plate']->mjid . '/delete';
}

/**
 * Sets the breadcrumb for administrative Grid Plate pages.
 */
function grid_plate_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Grid Plate'), 'admin/content/grid_plate'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
